#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_8__ {scalar_t__ journalMode; int /*<<< orphan*/  exclusiveMode; scalar_t__ pWal; scalar_t__ pTmpSpace; int /*<<< orphan*/  pageSize; int /*<<< orphan*/  walSyncFlags; int /*<<< orphan*/  zWal; int /*<<< orphan*/  pVfs; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ PAGER_JOURNALMODE_WAL ; 
 int /*<<< orphan*/  SHARED_LOCK ; 
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int pagerExclusiveLock (TYPE_1__*) ; 
 int /*<<< orphan*/  pagerFixMaplimit (TYPE_1__*) ; 
 int pagerLockDb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int pagerOpenWal (TYPE_1__*) ; 
 int /*<<< orphan*/  pagerUnlockDb (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sqlite3OsAccess (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int sqlite3WalClose (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int sqlite3PagerCloseWal(Pager *pPager, sqlite3 *db){
  int rc = SQLITE_OK;

  assert( pPager->journalMode==PAGER_JOURNALMODE_WAL );

  /* If the log file is not already open, but does exist in the file-system,
  ** it may need to be checkpointed before the connection can switch to
  ** rollback mode. Open it now so this can happen.
  */
  if( !pPager->pWal ){
    int logexists = 0;
    rc = pagerLockDb(pPager, SHARED_LOCK);
    if( rc==SQLITE_OK ){
      rc = sqlite3OsAccess(
          pPager->pVfs, pPager->zWal, SQLITE_ACCESS_EXISTS, &logexists
      );
    }
    if( rc==SQLITE_OK && logexists ){
      rc = pagerOpenWal(pPager);
    }
  }
    
  /* Checkpoint and close the log. Because an EXCLUSIVE lock is held on
  ** the database file, the log and log-summary files will be deleted.
  */
  if( rc==SQLITE_OK && pPager->pWal ){
    rc = pagerExclusiveLock(pPager);
    if( rc==SQLITE_OK ){
      rc = sqlite3WalClose(pPager->pWal, db, pPager->walSyncFlags,
                           pPager->pageSize, (u8*)pPager->pTmpSpace);
      pPager->pWal = 0;
      pagerFixMaplimit(pPager);
      if( rc && !pPager->exclusiveMode ) pagerUnlockDb(pPager, SHARED_LOCK);
    }
  }
  return rc;
}