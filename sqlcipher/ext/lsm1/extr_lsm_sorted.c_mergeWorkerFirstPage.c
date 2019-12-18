#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_9__ ;
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_21__ {scalar_t__ pPage; TYPE_6__* aSave; TYPE_5__* pDb; TYPE_3__* pLevel; TYPE_8__* pCsr; } ;
struct TYPE_20__ {int nPtr; int* pPrevMergePtr; TYPE_4__* aPtr; scalar_t__ pBtCsr; } ;
struct TYPE_19__ {int /*<<< orphan*/  iFirst; } ;
struct TYPE_18__ {int bStore; } ;
struct TYPE_17__ {int /*<<< orphan*/  pFS; } ;
struct TYPE_16__ {TYPE_7__* pSeg; } ;
struct TYPE_15__ {TYPE_2__* pNext; } ;
struct TYPE_13__ {scalar_t__ iFirst; } ;
struct TYPE_14__ {TYPE_1__ lhs; } ;
typedef  TYPE_7__ Segment ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_8__ MultiCursor ;
typedef  TYPE_9__ MergeWorker ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsDbPageGet (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int mergeWorkerNextPage (TYPE_9__*,int) ; 
 scalar_t__ pageGetPtr (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mergeWorkerFirstPage(MergeWorker *pMW){
  int rc = LSM_OK;                /* Return code */
  Page *pPg = 0;                  /* First page of run pSeg */
  int iFPtr = 0;                  /* Pointer value read from footer of pPg */
  MultiCursor *pCsr = pMW->pCsr;

  assert( pMW->pPage==0 );

  if( pCsr->pBtCsr ){
    rc = LSM_OK;
    iFPtr = (int)pMW->pLevel->pNext->lhs.iFirst;
  }else if( pCsr->nPtr>0 ){
    Segment *pSeg;
    pSeg = pCsr->aPtr[pCsr->nPtr-1].pSeg;
    rc = lsmFsDbPageGet(pMW->pDb->pFS, pSeg, pSeg->iFirst, &pPg);
    if( rc==LSM_OK ){
      u8 *aData;                    /* Buffer for page pPg */
      int nData;                    /* Size of aData[] in bytes */
      aData = fsPageData(pPg, &nData);
      iFPtr = (int)pageGetPtr(aData, nData);
      lsmFsPageRelease(pPg);
    }
  }

  if( rc==LSM_OK ){
    rc = mergeWorkerNextPage(pMW, iFPtr);
    if( pCsr->pPrevMergePtr ) *pCsr->pPrevMergePtr = iFPtr;
    pMW->aSave[0].bStore = 1;
  }

  return rc;
}