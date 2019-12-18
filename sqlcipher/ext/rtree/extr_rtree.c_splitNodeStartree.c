#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int sqlite3_int64 ;
struct TYPE_10__ {int nDim; } ;
typedef  int /*<<< orphan*/  RtreeNode ;
typedef  scalar_t__ RtreeDValue ;
typedef  int /*<<< orphan*/  RtreeCell ;
typedef  TYPE_1__ Rtree ;

/* Variables and functions */
 int RTREE_MINCELLS (TYPE_1__*) ; 
 scalar_t__ RTREE_ZERO ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SortByDimension (TYPE_1__*,int*,int,int,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ cellArea (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ cellMargin (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ cellOverlap (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cellUnion (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  memset (int**,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nodeInsertCell (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (int**) ; 
 scalar_t__ sqlite3_malloc64 (int) ; 

__attribute__((used)) static int splitNodeStartree(
  Rtree *pRtree,
  RtreeCell *aCell,
  int nCell,
  RtreeNode *pLeft,
  RtreeNode *pRight,
  RtreeCell *pBboxLeft,
  RtreeCell *pBboxRight
){
  int **aaSorted;
  int *aSpare;
  int ii;

  int iBestDim = 0;
  int iBestSplit = 0;
  RtreeDValue fBestMargin = RTREE_ZERO;

  sqlite3_int64 nByte = (pRtree->nDim+1)*(sizeof(int*)+nCell*sizeof(int));

  aaSorted = (int **)sqlite3_malloc64(nByte);
  if( !aaSorted ){
    return SQLITE_NOMEM;
  }

  aSpare = &((int *)&aaSorted[pRtree->nDim])[pRtree->nDim*nCell];
  memset(aaSorted, 0, nByte);
  for(ii=0; ii<pRtree->nDim; ii++){
    int jj;
    aaSorted[ii] = &((int *)&aaSorted[pRtree->nDim])[ii*nCell];
    for(jj=0; jj<nCell; jj++){
      aaSorted[ii][jj] = jj;
    }
    SortByDimension(pRtree, aaSorted[ii], nCell, ii, aCell, aSpare);
  }

  for(ii=0; ii<pRtree->nDim; ii++){
    RtreeDValue margin = RTREE_ZERO;
    RtreeDValue fBestOverlap = RTREE_ZERO;
    RtreeDValue fBestArea = RTREE_ZERO;
    int iBestLeft = 0;
    int nLeft;

    for(
      nLeft=RTREE_MINCELLS(pRtree); 
      nLeft<=(nCell-RTREE_MINCELLS(pRtree)); 
      nLeft++
    ){
      RtreeCell left;
      RtreeCell right;
      int kk;
      RtreeDValue overlap;
      RtreeDValue area;

      memcpy(&left, &aCell[aaSorted[ii][0]], sizeof(RtreeCell));
      memcpy(&right, &aCell[aaSorted[ii][nCell-1]], sizeof(RtreeCell));
      for(kk=1; kk<(nCell-1); kk++){
        if( kk<nLeft ){
          cellUnion(pRtree, &left, &aCell[aaSorted[ii][kk]]);
        }else{
          cellUnion(pRtree, &right, &aCell[aaSorted[ii][kk]]);
        }
      }
      margin += cellMargin(pRtree, &left);
      margin += cellMargin(pRtree, &right);
      overlap = cellOverlap(pRtree, &left, &right, 1);
      area = cellArea(pRtree, &left) + cellArea(pRtree, &right);
      if( (nLeft==RTREE_MINCELLS(pRtree))
       || (overlap<fBestOverlap)
       || (overlap==fBestOverlap && area<fBestArea)
      ){
        iBestLeft = nLeft;
        fBestOverlap = overlap;
        fBestArea = area;
      }
    }

    if( ii==0 || margin<fBestMargin ){
      iBestDim = ii;
      fBestMargin = margin;
      iBestSplit = iBestLeft;
    }
  }

  memcpy(pBboxLeft, &aCell[aaSorted[iBestDim][0]], sizeof(RtreeCell));
  memcpy(pBboxRight, &aCell[aaSorted[iBestDim][iBestSplit]], sizeof(RtreeCell));
  for(ii=0; ii<nCell; ii++){
    RtreeNode *pTarget = (ii<iBestSplit)?pLeft:pRight;
    RtreeCell *pBbox = (ii<iBestSplit)?pBboxLeft:pBboxRight;
    RtreeCell *pCell = &aCell[aaSorted[iBestDim][ii]];
    nodeInsertCell(pRtree, pTarget, pCell);
    cellUnion(pRtree, pBbox, pCell);
  }

  sqlite3_free(aaSorted);
  return SQLITE_OK;
}