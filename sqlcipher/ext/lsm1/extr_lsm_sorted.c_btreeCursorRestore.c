#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_15__ {int /*<<< orphan*/  member_2; int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int iPg; int nDepth; int eType; void* pKey; int nKey; TYPE_3__ blob; TYPE_4__* aPg; int /*<<< orphan*/  iPtr; int /*<<< orphan*/  pFS; TYPE_1__* pSeg; } ;
struct TYPE_16__ {int iCell; int /*<<< orphan*/ * pPage; } ;
struct TYPE_14__ {scalar_t__ iPg; int iCell; } ;
struct TYPE_13__ {int /*<<< orphan*/  pRedirect; scalar_t__ iRoot; } ;
typedef  TYPE_1__ Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_2__ MergeInput ;
typedef  scalar_t__ LsmPgno ;
typedef  TYPE_3__ LsmBlob ;
typedef  TYPE_4__ BtreePg ;
typedef  TYPE_5__ BtreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int LSM_SEPARATOR ; 
 int SEGMENT_BTREE_FLAG ; 
 int /*<<< orphan*/  assert (int) ; 
 int btreeCursorLoadKey (TYPE_5__*) ; 
 int /*<<< orphan*/  btreeCursorPtr (int /*<<< orphan*/ *,int,scalar_t__) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ ,TYPE_1__*,int,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/ * lsmFsEnv (int /*<<< orphan*/ ) ; 
 scalar_t__ lsmFsRedirectPage (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 scalar_t__ lsmMallocZeroRc (int /*<<< orphan*/ *,int,int*) ; 
 int pageGetBtreeKey (TYPE_1__*,int /*<<< orphan*/ *,int,scalar_t__*,int*,void**,int*,TYPE_3__*) ; 
 int pageGetFlags (int /*<<< orphan*/ *,int) ; 
 int pageGetNRec (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pageGetPtr (int /*<<< orphan*/ *,int) ; 
 scalar_t__ pageObjGetNRec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sortedBlobFree (TYPE_3__*) ; 
 int sortedKeyCompare (int (*) (void*,int,void*,int),int,void*,int,int,void*,int) ; 

__attribute__((used)) static int btreeCursorRestore(
  BtreeCursor *pCsr, 
  int (*xCmp)(void *, int, void *, int),
  MergeInput *p
){
  int rc = LSM_OK;

  if( p->iPg ){
    lsm_env *pEnv = lsmFsEnv(pCsr->pFS);
    int iCell;                    /* Current cell number on leaf page */
    LsmPgno iLeaf;                /* Page number of current leaf page */
    int nDepth;                   /* Depth of b-tree structure */
    Segment *pSeg = pCsr->pSeg;

    /* Decode the MergeInput structure */
    iLeaf = p->iPg;
    nDepth = (p->iCell & 0x00FF);
    iCell = (p->iCell >> 8) - 1;

    /* Allocate the BtreeCursor.aPg[] array */
    assert( pCsr->aPg==0 );
    pCsr->aPg = (BtreePg *)lsmMallocZeroRc(pEnv, sizeof(BtreePg) * nDepth, &rc);

    /* Populate the last entry of the aPg[] array */
    if( rc==LSM_OK ){
      Page **pp = &pCsr->aPg[nDepth-1].pPage;
      pCsr->iPg = nDepth-1;
      pCsr->nDepth = nDepth;
      pCsr->aPg[pCsr->iPg].iCell = iCell;
      rc = lsmFsDbPageGet(pCsr->pFS, pSeg, iLeaf, pp);
    }

    /* Populate any other aPg[] array entries */
    if( rc==LSM_OK && nDepth>1 ){
      LsmBlob blob = {0,0,0};
      void *pSeek;
      int nSeek;
      int iTopicSeek;
      int iPg = 0;
      int iLoad = (int)pSeg->iRoot;
      Page *pPg = pCsr->aPg[nDepth-1].pPage;
 
      if( pageObjGetNRec(pPg)==0 ){
        /* This can happen when pPg is the right-most leaf in the b-tree.
        ** In this case, set the iTopicSeek/pSeek/nSeek key to a value
        ** greater than any real key.  */
        assert( iCell==-1 );
        iTopicSeek = 1000;
        pSeek = 0;
        nSeek = 0;
      }else{
        LsmPgno dummy;
        rc = pageGetBtreeKey(pSeg, pPg,
            0, &dummy, &iTopicSeek, &pSeek, &nSeek, &pCsr->blob
        );
      }

      do {
        Page *pPg2;
        rc = lsmFsDbPageGet(pCsr->pFS, pSeg, iLoad, &pPg2);
        assert( rc==LSM_OK || pPg2==0 );
        if( rc==LSM_OK ){
          u8 *aData;                  /* Buffer containing page data */
          int nData;                  /* Size of aData[] in bytes */
          int iMin;
          int iMax;
          int iCell2;

          aData = fsPageData(pPg2, &nData);
          assert( (pageGetFlags(aData, nData) & SEGMENT_BTREE_FLAG) );

          iLoad = (int)pageGetPtr(aData, nData);
          iCell2 = pageGetNRec(aData, nData); 
          iMax = iCell2-1;
          iMin = 0;

          while( iMax>=iMin ){
            int iTry = (iMin+iMax)/2;
            void *pKey; int nKey;         /* Key for cell iTry */
            int iTopic;                   /* Topic for key pKeyT/nKeyT */
            LsmPgno iPtr;                 /* Pointer for cell iTry */
            int res;                      /* (pSeek - pKeyT) */

            rc = pageGetBtreeKey(
                pSeg, pPg2, iTry, &iPtr, &iTopic, &pKey, &nKey, &blob
            );
            if( rc!=LSM_OK ) break;

            res = sortedKeyCompare(
                xCmp, iTopicSeek, pSeek, nSeek, iTopic, pKey, nKey
            );
            assert( res!=0 );

            if( res<0 ){
              iLoad = (int)iPtr;
              iCell2 = iTry;
              iMax = iTry-1;
            }else{
              iMin = iTry+1;
            }
          }

          pCsr->aPg[iPg].pPage = pPg2;
          pCsr->aPg[iPg].iCell = iCell2;
          iPg++;
          assert( iPg!=nDepth-1 
               || lsmFsRedirectPage(pCsr->pFS, pSeg->pRedirect, iLoad)==iLeaf
          );
        }
      }while( rc==LSM_OK && iPg<(nDepth-1) );
      sortedBlobFree(&blob);
    }

    /* Load the current key and pointer */
    if( rc==LSM_OK ){
      BtreePg *pBtreePg;
      u8 *aData;
      int nData;

      pBtreePg = &pCsr->aPg[pCsr->iPg];
      aData = fsPageData(pBtreePg->pPage, &nData);
      pCsr->iPtr = btreeCursorPtr(aData, nData, pBtreePg->iCell+1);
      if( pBtreePg->iCell<0 ){
        LsmPgno dummy;
        int i;
        for(i=pCsr->iPg-1; i>=0; i--){
          if( pCsr->aPg[i].iCell>0 ) break;
        }
        assert( i>=0 );
        rc = pageGetBtreeKey(pSeg,
            pCsr->aPg[i].pPage, pCsr->aPg[i].iCell-1,
            &dummy, &pCsr->eType, &pCsr->pKey, &pCsr->nKey, &pCsr->blob
        );
        pCsr->eType |= LSM_SEPARATOR;

      }else{
        rc = btreeCursorLoadKey(pCsr);
      }
    }
  }
  return rc;
}