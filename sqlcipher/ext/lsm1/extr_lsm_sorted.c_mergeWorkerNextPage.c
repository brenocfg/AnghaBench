#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_10__ {scalar_t__ xCompress; } ;
struct TYPE_12__ {TYPE_2__ compress; int /*<<< orphan*/  pWorker; int /*<<< orphan*/  pFS; } ;
typedef  TYPE_4__ lsm_db ;
struct TYPE_9__ {scalar_t__ iFirst; } ;
struct TYPE_14__ {TYPE_3__* pMerge; TYPE_1__ lhs; } ;
struct TYPE_13__ {int /*<<< orphan*/  nWork; TYPE_8__* pLevel; int /*<<< orphan*/ * pPage; TYPE_4__* pDb; } ;
struct TYPE_11__ {scalar_t__ iOutputOff; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_5__ MergeWorker ;
typedef  int /*<<< orphan*/  LsmPgno ;

/* Variables and functions */
 int LSM_OK ; 
 size_t SEGMENT_FLAGS_OFFSET (int) ; 
 size_t SEGMENT_NRECORD_OFFSET (int) ; 
 size_t SEGMENT_POINTER_OFFSET (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int lsmFsSortedAppend (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmPutU16 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmPutU64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int mergeWorkerPersistAndRelease (TYPE_5__*) ; 

__attribute__((used)) static int mergeWorkerNextPage(
  MergeWorker *pMW,               /* Merge worker object to append page to */
  LsmPgno iFPtr                   /* Pointer value for footer of new page */
){
  int rc = LSM_OK;                /* Return code */
  Page *pNext = 0;                /* New page appended to run */
  lsm_db *pDb = pMW->pDb;         /* Database handle */

  rc = lsmFsSortedAppend(pDb->pFS, pDb->pWorker, pMW->pLevel, 0, &pNext);
  assert( rc || pMW->pLevel->lhs.iFirst>0 || pMW->pDb->compress.xCompress );

  if( rc==LSM_OK ){
    u8 *aData;                    /* Data buffer belonging to page pNext */
    int nData;                    /* Size of aData[] in bytes */

    rc = mergeWorkerPersistAndRelease(pMW);

    pMW->pPage = pNext;
    pMW->pLevel->pMerge->iOutputOff = 0;
    aData = fsPageData(pNext, &nData);
    lsmPutU16(&aData[SEGMENT_NRECORD_OFFSET(nData)], 0);
    lsmPutU16(&aData[SEGMENT_FLAGS_OFFSET(nData)], 0);
    lsmPutU64(&aData[SEGMENT_POINTER_OFFSET(nData)], iFPtr);
    pMW->nWork++;
  }

  return rc;
}