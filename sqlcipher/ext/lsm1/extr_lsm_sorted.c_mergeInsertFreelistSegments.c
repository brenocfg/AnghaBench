#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_17__ {int /*<<< orphan*/  pEnv; TYPE_1__* pWorker; } ;
typedef  TYPE_2__ lsm_db ;
struct TYPE_18__ {struct TYPE_18__* pSeg; TYPE_7__* pLevel; } ;
struct TYPE_21__ {int nRight; TYPE_3__* aRhs; struct TYPE_21__* pNext; TYPE_3__ lhs; } ;
struct TYPE_20__ {TYPE_3__* aGobble; TYPE_7__* pLevel; TYPE_5__* pCsr; } ;
struct TYPE_19__ {int nPtr; TYPE_3__* aPtr; TYPE_3__* aTree; } ;
struct TYPE_16__ {TYPE_7__* pLevel; } ;
typedef  TYPE_3__ SegmentPtr ;
typedef  TYPE_3__ Segment ;
typedef  TYPE_5__ MultiCursor ;
typedef  TYPE_6__ MergeWorker ;
typedef  TYPE_7__ Level ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,TYPE_3__*) ; 
 scalar_t__ lsmMallocZeroRc (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int segmentPtrEnd (TYPE_5__*,TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sortedFreeLevel (int /*<<< orphan*/ ,TYPE_7__*) ; 

__attribute__((used)) static int mergeInsertFreelistSegments(
  lsm_db *pDb, 
  int nFree,
  MergeWorker *pMW
){
  int rc = LSM_OK;
  if( nFree>0 ){
    MultiCursor *pCsr = pMW->pCsr;
    Level *pLvl = pMW->pLevel;
    SegmentPtr *aNew1;
    Segment *aNew2;

    Level *pIter;
    Level *pNext;
    int i = 0;

    aNew1 = (SegmentPtr *)lsmMallocZeroRc(
        pDb->pEnv, sizeof(SegmentPtr) * (pCsr->nPtr+nFree), &rc
    );
    if( rc ) return rc;
    memcpy(&aNew1[nFree], pCsr->aPtr, sizeof(SegmentPtr)*pCsr->nPtr);
    pCsr->nPtr += nFree;
    lsmFree(pDb->pEnv, pCsr->aTree);
    lsmFree(pDb->pEnv, pCsr->aPtr);
    pCsr->aTree = 0;
    pCsr->aPtr = aNew1;

    aNew2 = (Segment *)lsmMallocZeroRc(
        pDb->pEnv, sizeof(Segment) * (pLvl->nRight+nFree), &rc
    );
    if( rc ) return rc;
    memcpy(&aNew2[nFree], pLvl->aRhs, sizeof(Segment)*pLvl->nRight);
    pLvl->nRight += nFree;
    lsmFree(pDb->pEnv, pLvl->aRhs);
    pLvl->aRhs = aNew2;

    for(pIter=pDb->pWorker->pLevel; rc==LSM_OK && pIter!=pLvl; pIter=pNext){
      Segment *pSeg = &pLvl->aRhs[i];
      memcpy(pSeg, &pIter->lhs, sizeof(Segment));

      pCsr->aPtr[i].pSeg = pSeg;
      pCsr->aPtr[i].pLevel = pLvl;
      rc = segmentPtrEnd(pCsr, &pCsr->aPtr[i], 0);

      pDb->pWorker->pLevel = pNext = pIter->pNext;
      sortedFreeLevel(pDb->pEnv, pIter);
      i++;
    }
    assert( i==nFree );
    assert( rc!=LSM_OK || pDb->pWorker->pLevel==pLvl );

    for(i=nFree; i<pCsr->nPtr; i++){
      pCsr->aPtr[i].pSeg = &pLvl->aRhs[i];
    }

    lsmFree(pDb->pEnv, pMW->aGobble);
    pMW->aGobble = 0;
  }
  return rc;
}