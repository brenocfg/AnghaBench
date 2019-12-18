#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_12__ {int nHier; int /*<<< orphan*/ ** apHier; } ;
struct TYPE_13__ {TYPE_5__ hier; TYPE_4__* pDb; TYPE_3__* pLevel; TYPE_1__* aSave; } ;
struct TYPE_11__ {int /*<<< orphan*/  pEnv; } ;
struct TYPE_9__ {int /*<<< orphan*/  iRoot; } ;
struct TYPE_10__ {TYPE_2__ lhs; } ;
struct TYPE_8__ {int /*<<< orphan*/  iPgno; } ;
typedef  int /*<<< orphan*/  Page ;
typedef  TYPE_6__ MergeWorker ;
typedef  int /*<<< orphan*/  LsmPgno ;

/* Variables and functions */
 int LSM_OK ; 
 size_t SEGMENT_POINTER_OFFSET (int) ; 
 int /*<<< orphan*/ * fsPageData (int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  lsmFsPageNumber (int /*<<< orphan*/ *) ; 
 int lsmFsPagePersist (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmFsPageRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmPutU64 (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int mergeWorkerFinishHierarchy(
  MergeWorker *pMW                /* Merge worker object */
){
  int i;                          /* Used to loop through apHier[] */
  int rc = LSM_OK;                /* Return code */
  LsmPgno iPtr;                   /* New right-hand-child pointer value */

  iPtr = pMW->aSave[0].iPgno;
  for(i=0; i<pMW->hier.nHier && rc==LSM_OK; i++){
    Page *pPg = pMW->hier.apHier[i];
    int nData;                    /* Size of aData[] in bytes */
    u8 *aData;                    /* Page data for pPg */

    aData = fsPageData(pPg, &nData);
    lsmPutU64(&aData[SEGMENT_POINTER_OFFSET(nData)], iPtr);

    rc = lsmFsPagePersist(pPg);
    iPtr = lsmFsPageNumber(pPg);
    lsmFsPageRelease(pPg);
  }

  if( pMW->hier.nHier ){
    pMW->pLevel->lhs.iRoot = iPtr;
    lsmFree(pMW->pDb->pEnv, pMW->hier.apHier);
    pMW->hier.apHier = 0;
    pMW->hier.nHier = 0;
  }

  return rc;
}