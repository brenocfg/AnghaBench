#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int eState; int errCode; int /*<<< orphan*/  jfd; int /*<<< orphan*/  setMaster; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int /*<<< orphan*/  MEMDB ; 
 int /*<<< orphan*/  PAGERID (TYPE_1__*) ; 
 int /*<<< orphan*/  PAGERTRACE (char*) ; 
 int PAGER_ERROR ; 
 int PAGER_READER ; 
 int PAGER_WRITER_LOCKED ; 
 int /*<<< orphan*/  SAVEPOINT_ROLLBACK ; 
 int SQLITE_ABORT ; 
 int SQLITE_CANTOPEN ; 
 int SQLITE_CORRUPT ; 
 int SQLITE_FULL ; 
 int SQLITE_IOERR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 int /*<<< orphan*/  isOpen (int /*<<< orphan*/ ) ; 
 scalar_t__ pagerUseWal (TYPE_1__*) ; 
 int pager_end_transaction (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pager_error (TYPE_1__*,int) ; 
 int pager_playback (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setGetterMethod (TYPE_1__*) ; 
 int sqlite3PagerSavepoint (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int sqlite3PagerRollback(Pager *pPager){
  int rc = SQLITE_OK;                  /* Return code */
  PAGERTRACE(("ROLLBACK %d\n", PAGERID(pPager)));

  /* PagerRollback() is a no-op if called in READER or OPEN state. If
  ** the pager is already in the ERROR state, the rollback is not 
  ** attempted here. Instead, the error code is returned to the caller.
  */
  assert( assert_pager_state(pPager) );
  if( pPager->eState==PAGER_ERROR ) return pPager->errCode;
  if( pPager->eState<=PAGER_READER ) return SQLITE_OK;

  if( pagerUseWal(pPager) ){
    int rc2;
    rc = sqlite3PagerSavepoint(pPager, SAVEPOINT_ROLLBACK, -1);
    rc2 = pager_end_transaction(pPager, pPager->setMaster, 0);
    if( rc==SQLITE_OK ) rc = rc2;
  }else if( !isOpen(pPager->jfd) || pPager->eState==PAGER_WRITER_LOCKED ){
    int eState = pPager->eState;
    rc = pager_end_transaction(pPager, 0, 0);
    if( !MEMDB && eState>PAGER_WRITER_LOCKED ){
      /* This can happen using journal_mode=off. Move the pager to the error 
      ** state to indicate that the contents of the cache may not be trusted.
      ** Any active readers will get SQLITE_ABORT.
      */
      pPager->errCode = SQLITE_ABORT;
      pPager->eState = PAGER_ERROR;
      setGetterMethod(pPager);
      return rc;
    }
  }else{
    rc = pager_playback(pPager, 0);
  }

  assert( pPager->eState==PAGER_READER || rc!=SQLITE_OK );
  assert( rc==SQLITE_OK || rc==SQLITE_FULL || rc==SQLITE_CORRUPT
          || rc==SQLITE_NOMEM || (rc&0xFF)==SQLITE_IOERR 
          || rc==SQLITE_CANTOPEN
  );

  /* If an error occurs during a ROLLBACK, we can no longer trust the pager
  ** cache. So call pager_error() on the way out to make any error persistent.
  */
  return pager_error(pPager, rc);
}