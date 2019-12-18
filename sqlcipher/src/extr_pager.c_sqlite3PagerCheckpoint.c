#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_4__ {scalar_t__ pTmpSpace; int /*<<< orphan*/  pageSize; int /*<<< orphan*/  walSyncFlags; int /*<<< orphan*/  pBusyHandlerArg; int /*<<< orphan*/  xBusyHandler; scalar_t__ pWal; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int SQLITE_CHECKPOINT_PASSIVE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  sqlite3PagerResetLockTimeout (TYPE_1__*) ; 
 int sqlite3WalCheckpoint (scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*,int*) ; 

int sqlite3PagerCheckpoint(
  Pager *pPager,                  /* Checkpoint on this pager */
  sqlite3 *db,                    /* Db handle used to check for interrupts */
  int eMode,                      /* Type of checkpoint */
  int *pnLog,                     /* OUT: Final number of frames in log */
  int *pnCkpt                     /* OUT: Final number of checkpointed frames */
){
  int rc = SQLITE_OK;
  if( pPager->pWal ){
    rc = sqlite3WalCheckpoint(pPager->pWal, db, eMode,
        (eMode==SQLITE_CHECKPOINT_PASSIVE ? 0 : pPager->xBusyHandler),
        pPager->pBusyHandlerArg,
        pPager->walSyncFlags, pPager->pageSize, (u8 *)pPager->pTmpSpace,
        pnLog, pnCkpt
    );
    sqlite3PagerResetLockTimeout(pPager);
  }
  return rc;
}