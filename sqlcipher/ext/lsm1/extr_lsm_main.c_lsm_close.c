#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_4__* aArray; } ;
struct TYPE_13__ {int /*<<< orphan*/  pCtx; int /*<<< orphan*/  (* xFree ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_12__ {int /*<<< orphan*/  pCtx; int /*<<< orphan*/  (* xFree ) (int /*<<< orphan*/ ) ;} ;
struct TYPE_15__ {int /*<<< orphan*/  pEnv; struct TYPE_15__* apShm; struct TYPE_15__* aTrans; TYPE_3__ rollback; TYPE_2__ compress; TYPE_1__ factory; int /*<<< orphan*/  pFS; scalar_t__ pClient; scalar_t__ nTransOpen; scalar_t__ pCsr; } ;
typedef  TYPE_4__ lsm_db ;

/* Variables and functions */
 int LSM_MISUSE_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assertRwclientLockValue (TYPE_4__*) ; 
 int /*<<< orphan*/  assert_db_state (TYPE_4__*) ; 
 int /*<<< orphan*/  lsmDbDatabaseRelease (TYPE_4__*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,TYPE_4__*) ; 
 int /*<<< orphan*/  lsmFreeSnapshot (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lsmFsClose (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmLogClose (TYPE_4__*) ; 
 int /*<<< orphan*/  lsmMCursorFreeCache (TYPE_4__*) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ ) ; 

int lsm_close(lsm_db *pDb){
  int rc = LSM_OK;
  if( pDb ){
    assert_db_state(pDb);
    if( pDb->pCsr || pDb->nTransOpen ){
      rc = LSM_MISUSE_BKPT;
    }else{
      lsmMCursorFreeCache(pDb);
      lsmFreeSnapshot(pDb->pEnv, pDb->pClient);
      pDb->pClient = 0;

      assertRwclientLockValue(pDb);

      lsmDbDatabaseRelease(pDb);
      lsmLogClose(pDb);
      lsmFsClose(pDb->pFS);
      /* assert( pDb->mLock==0 ); */
      
      /* Invoke any destructors registered for the compression or 
      ** compression factory callbacks.  */
      if( pDb->factory.xFree ) pDb->factory.xFree(pDb->factory.pCtx);
      if( pDb->compress.xFree ) pDb->compress.xFree(pDb->compress.pCtx);

      lsmFree(pDb->pEnv, pDb->rollback.aArray);
      lsmFree(pDb->pEnv, pDb->aTrans);
      lsmFree(pDb->pEnv, pDb->apShm);
      lsmFree(pDb->pEnv, pDb);
    }
  }
  return rc;
}