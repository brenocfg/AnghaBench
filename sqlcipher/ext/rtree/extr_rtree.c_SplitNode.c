#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_47__   TYPE_3__ ;
typedef  struct TYPE_46__   TYPE_2__ ;
typedef  struct TYPE_45__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_47__ {int iNodeSize; int /*<<< orphan*/  iDepth; } ;
struct TYPE_46__ {scalar_t__ iRowid; } ;
struct TYPE_45__ {int iNode; int isDirty; int* zData; struct TYPE_45__* pParent; int /*<<< orphan*/  nRef; } ;
typedef  TYPE_1__ RtreeNode ;
typedef  TYPE_2__ RtreeCell ;
typedef  TYPE_3__ Rtree ;

/* Variables and functions */
 int AdjustTree (TYPE_3__*,TYPE_1__*,TYPE_2__*) ; 
 int NCELL (TYPE_1__*) ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  memcpy (TYPE_2__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  memset (int*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nodeGetCell (TYPE_3__*,TYPE_1__*,int,TYPE_2__*) ; 
 scalar_t__ nodeGetRowid (TYPE_3__*,TYPE_1__*,int) ; 
 TYPE_1__* nodeNew (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nodeOverwriteCell (TYPE_3__*,TYPE_1__*,TYPE_2__*,int) ; 
 int nodeParentIndex (TYPE_3__*,TYPE_1__*,int*) ; 
 int nodeRelease (TYPE_3__*,TYPE_1__*) ; 
 int nodeWrite (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  nodeZero (TYPE_3__*,TYPE_1__*) ; 
 int rtreeInsertCell (TYPE_3__*,TYPE_1__*,TYPE_2__*,int) ; 
 int splitNodeStartree (TYPE_3__*,TYPE_2__*,int,TYPE_1__*,TYPE_1__*,TYPE_2__*,TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 TYPE_2__* sqlite3_malloc64 (int) ; 
 int updateMapping (TYPE_3__*,scalar_t__,TYPE_1__*,int) ; 
 int /*<<< orphan*/  writeInt16 (int*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int SplitNode(
  Rtree *pRtree,
  RtreeNode *pNode,
  RtreeCell *pCell,
  int iHeight
){
  int i;
  int newCellIsRight = 0;

  int rc = SQLITE_OK;
  int nCell = NCELL(pNode);
  RtreeCell *aCell;
  int *aiUsed;

  RtreeNode *pLeft = 0;
  RtreeNode *pRight = 0;

  RtreeCell leftbbox;
  RtreeCell rightbbox;

  /* Allocate an array and populate it with a copy of pCell and 
  ** all cells from node pLeft. Then zero the original node.
  */
  aCell = sqlite3_malloc64((sizeof(RtreeCell)+sizeof(int))*(nCell+1));
  if( !aCell ){
    rc = SQLITE_NOMEM;
    goto splitnode_out;
  }
  aiUsed = (int *)&aCell[nCell+1];
  memset(aiUsed, 0, sizeof(int)*(nCell+1));
  for(i=0; i<nCell; i++){
    nodeGetCell(pRtree, pNode, i, &aCell[i]);
  }
  nodeZero(pRtree, pNode);
  memcpy(&aCell[nCell], pCell, sizeof(RtreeCell));
  nCell++;

  if( pNode->iNode==1 ){
    pRight = nodeNew(pRtree, pNode);
    pLeft = nodeNew(pRtree, pNode);
    pRtree->iDepth++;
    pNode->isDirty = 1;
    writeInt16(pNode->zData, pRtree->iDepth);
  }else{
    pLeft = pNode;
    pRight = nodeNew(pRtree, pLeft->pParent);
    pLeft->nRef++;
  }

  if( !pLeft || !pRight ){
    rc = SQLITE_NOMEM;
    goto splitnode_out;
  }

  memset(pLeft->zData, 0, pRtree->iNodeSize);
  memset(pRight->zData, 0, pRtree->iNodeSize);

  rc = splitNodeStartree(pRtree, aCell, nCell, pLeft, pRight,
                         &leftbbox, &rightbbox);
  if( rc!=SQLITE_OK ){
    goto splitnode_out;
  }

  /* Ensure both child nodes have node numbers assigned to them by calling
  ** nodeWrite(). Node pRight always needs a node number, as it was created
  ** by nodeNew() above. But node pLeft sometimes already has a node number.
  ** In this case avoid the all to nodeWrite().
  */
  if( SQLITE_OK!=(rc = nodeWrite(pRtree, pRight))
   || (0==pLeft->iNode && SQLITE_OK!=(rc = nodeWrite(pRtree, pLeft)))
  ){
    goto splitnode_out;
  }

  rightbbox.iRowid = pRight->iNode;
  leftbbox.iRowid = pLeft->iNode;

  if( pNode->iNode==1 ){
    rc = rtreeInsertCell(pRtree, pLeft->pParent, &leftbbox, iHeight+1);
    if( rc!=SQLITE_OK ){
      goto splitnode_out;
    }
  }else{
    RtreeNode *pParent = pLeft->pParent;
    int iCell;
    rc = nodeParentIndex(pRtree, pLeft, &iCell);
    if( rc==SQLITE_OK ){
      nodeOverwriteCell(pRtree, pParent, &leftbbox, iCell);
      rc = AdjustTree(pRtree, pParent, &leftbbox);
    }
    if( rc!=SQLITE_OK ){
      goto splitnode_out;
    }
  }
  if( (rc = rtreeInsertCell(pRtree, pRight->pParent, &rightbbox, iHeight+1)) ){
    goto splitnode_out;
  }

  for(i=0; i<NCELL(pRight); i++){
    i64 iRowid = nodeGetRowid(pRtree, pRight, i);
    rc = updateMapping(pRtree, iRowid, pRight, iHeight);
    if( iRowid==pCell->iRowid ){
      newCellIsRight = 1;
    }
    if( rc!=SQLITE_OK ){
      goto splitnode_out;
    }
  }
  if( pNode->iNode==1 ){
    for(i=0; i<NCELL(pLeft); i++){
      i64 iRowid = nodeGetRowid(pRtree, pLeft, i);
      rc = updateMapping(pRtree, iRowid, pLeft, iHeight);
      if( rc!=SQLITE_OK ){
        goto splitnode_out;
      }
    }
  }else if( newCellIsRight==0 ){
    rc = updateMapping(pRtree, pCell->iRowid, pLeft, iHeight);
  }

  if( rc==SQLITE_OK ){
    rc = nodeRelease(pRtree, pRight);
    pRight = 0;
  }
  if( rc==SQLITE_OK ){
    rc = nodeRelease(pRtree, pLeft);
    pLeft = 0;
  }

splitnode_out:
  nodeRelease(pRtree, pRight);
  nodeRelease(pRtree, pLeft);
  sqlite3_free(aCell);
  return rc;
}