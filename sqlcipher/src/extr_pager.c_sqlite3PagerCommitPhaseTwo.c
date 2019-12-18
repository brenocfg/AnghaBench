#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int errCode; scalar_t__ eState; scalar_t__ journalMode; scalar_t__ journalOff; int /*<<< orphan*/  setMaster; int /*<<< orphan*/  iDataVersion; scalar_t__ exclusiveMode; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ JOURNAL_HDR_SZ (TYPE_1__*) ; 
 scalar_t__ NEVER (int) ; 
 int /*<<< orphan*/  PAGERID (TYPE_1__*) ; 
 int /*<<< orphan*/  PAGERTRACE (char*) ; 
 scalar_t__ PAGER_JOURNALMODE_PERSIST ; 
 scalar_t__ PAGER_READER ; 
 scalar_t__ PAGER_WRITER_CACHEMOD ; 
 scalar_t__ PAGER_WRITER_FINISHED ; 
 scalar_t__ PAGER_WRITER_LOCKED ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 scalar_t__ pagerUseWal (TYPE_1__*) ; 
 int pager_end_transaction (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int pager_error (TYPE_1__*,int) ; 

int sqlite3PagerCommitPhaseTwo(Pager *pPager){
  int rc = SQLITE_OK;                  /* Return code */

  /* This routine should not be called if a prior error has occurred.
  ** But if (due to a coding error elsewhere in the system) it does get
  ** called, just return the same error code without doing anything. */
  if( NEVER(pPager->errCode) ) return pPager->errCode;

  assert( pPager->eState==PAGER_WRITER_LOCKED
       || pPager->eState==PAGER_WRITER_FINISHED
       || (pagerUseWal(pPager) && pPager->eState==PAGER_WRITER_CACHEMOD)
  );
  assert( assert_pager_state(pPager) );

  /* An optimization. If the database was not actually modified during
  ** this transaction, the pager is running in exclusive-mode and is
  ** using persistent journals, then this function is a no-op.
  **
  ** The start of the journal file currently contains a single journal 
  ** header with the nRec field set to 0. If such a journal is used as
  ** a hot-journal during hot-journal rollback, 0 changes will be made
  ** to the database file. So there is no need to zero the journal 
  ** header. Since the pager is in exclusive mode, there is no need
  ** to drop any locks either.
  */
  if( pPager->eState==PAGER_WRITER_LOCKED 
   && pPager->exclusiveMode 
   && pPager->journalMode==PAGER_JOURNALMODE_PERSIST
  ){
    assert( pPager->journalOff==JOURNAL_HDR_SZ(pPager) || !pPager->journalOff );
    pPager->eState = PAGER_READER;
    return SQLITE_OK;
  }

  PAGERTRACE(("COMMIT %d\n", PAGERID(pPager)));
  pPager->iDataVersion++;
  rc = pager_end_transaction(pPager, pPager->setMaster, 1);
  return pager_error(pPager, rc);
}