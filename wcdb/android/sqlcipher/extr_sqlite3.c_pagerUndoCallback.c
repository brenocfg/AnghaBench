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
struct TYPE_4__ {int /*<<< orphan*/  pBackup; int /*<<< orphan*/  (* xReiniter ) (int /*<<< orphan*/ *) ;} ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  int /*<<< orphan*/  PgHdr ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pagerUseWal (TYPE_1__*) ; 
 int readDbPage (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3BackupRestart (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite3PagerLookup (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerUnrefNotNull (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3PcacheDrop (int /*<<< orphan*/ *) ; 
 int sqlite3PcachePageRefcount (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int pagerUndoCallback(void *pCtx, Pgno iPg){
  int rc = SQLITE_OK;
  Pager *pPager = (Pager *)pCtx;
  PgHdr *pPg;

  assert( pagerUseWal(pPager) );
  pPg = sqlite3PagerLookup(pPager, iPg);
  if( pPg ){
    if( sqlite3PcachePageRefcount(pPg)==1 ){
      sqlite3PcacheDrop(pPg);
    }else{
      rc = readDbPage(pPg);
      if( rc==SQLITE_OK ){
        pPager->xReiniter(pPg);
      }
      sqlite3PagerUnrefNotNull(pPg);
    }
  }

  /* Normally, if a transaction is rolled back, any backup processes are
  ** updated as data is copied out of the rollback journal and into the
  ** database. This is not generally possible with a WAL database, as
  ** rollback involves simply truncating the log file. Therefore, if one
  ** or more frames have already been written to the log (and therefore 
  ** also copied into the backup databases) as part of this transaction,
  ** the backups must be restarted.
  */
  sqlite3BackupRestart(pPager->pBackup);

  return rc;
}