#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_9__ {TYPE_2__* aSave; scalar_t__ iIndirect; TYPE_1__* pDb; } ;
struct TYPE_8__ {int bStore; scalar_t__ iPgno; } ;
struct TYPE_7__ {int /*<<< orphan*/  pFS; } ;
typedef  TYPE_3__ MergeWorker ;
typedef  scalar_t__ LsmPgno ;

/* Variables and functions */
 int LSM_OK ; 
 int LSM_SEPARATOR ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmFsPageSize (int /*<<< orphan*/ ) ; 
 int mergeWorkerBtreeIndirect (TYPE_3__*) ; 
 int mergeWorkerBtreeWrite (TYPE_3__*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,void*,int) ; 

__attribute__((used)) static int mergeWorkerPushHierarchy(
  MergeWorker *pMW,               /* Merge worker object */
  int iTopic,                     /* Topic value for this key */
  void *pKey,                     /* Pointer to key buffer */
  int nKey                        /* Size of pKey buffer in bytes */
){
  int rc = LSM_OK;                /* Return Code */
  LsmPgno iPtr;                   /* Pointer value to accompany pKey/nKey */

  assert( pMW->aSave[0].bStore==0 );
  assert( pMW->aSave[1].bStore==0 );
  rc = mergeWorkerBtreeIndirect(pMW);

  /* Obtain the absolute pointer value to store along with the key in the
  ** page body. This pointer points to a page that contains keys that are
  ** smaller than pKey/nKey.  */
  iPtr = pMW->aSave[0].iPgno;
  assert( iPtr!=0 );

  /* Determine if the indirect format should be used. */
  if( (nKey*4 > lsmFsPageSize(pMW->pDb->pFS)) ){
    pMW->iIndirect = iPtr;
    pMW->aSave[1].bStore = 1;
  }else{
    rc = mergeWorkerBtreeWrite(
        pMW, (u8)(iTopic | LSM_SEPARATOR), iPtr, 0, pKey, nKey
    );
  }

  /* Ensure that the SortedRun.iRoot field is correct. */
  return rc;
}