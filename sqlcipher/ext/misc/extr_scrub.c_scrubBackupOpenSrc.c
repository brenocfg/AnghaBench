#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {scalar_t__ pMethods; } ;
struct TYPE_6__ {scalar_t__ rcErr; TYPE_2__* pSrc; int /*<<< orphan*/  dbSrc; void* nPage; void* szPage; int /*<<< orphan*/  zSrcFile; } ;
typedef  TYPE_1__ ScrubState ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_CHECKPOINT_FULL ; 
 scalar_t__ SQLITE_ERROR ; 
 int /*<<< orphan*/  SQLITE_FCNTL_FILE_POINTER ; 
 int SQLITE_OPEN_PRIVATECACHE ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_URI ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  scrubBackupErr (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/ * scrubBackupPrepare (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 void* sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_file_control (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_open_v2 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 int sqlite3_wal_checkpoint_v2 (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void scrubBackupOpenSrc(ScrubState *p){
  sqlite3_stmt *pStmt;
  int rc;
  /* Open the source database file */
  p->rcErr = sqlite3_open_v2(p->zSrcFile, &p->dbSrc,
                 SQLITE_OPEN_READWRITE |
                 SQLITE_OPEN_URI | SQLITE_OPEN_PRIVATECACHE, 0);
  if( p->rcErr ){
    scrubBackupErr(p, "cannot open source database: %s",
                      sqlite3_errmsg(p->dbSrc));
    return;
  }
  p->rcErr = sqlite3_exec(p->dbSrc, "SELECT 1 FROM sqlite_master; BEGIN;",
                          0, 0, 0);
  if( p->rcErr ){
    scrubBackupErr(p,
       "cannot start a read transaction on the source database: %s",
       sqlite3_errmsg(p->dbSrc));
    return;
  }
  rc = sqlite3_wal_checkpoint_v2(p->dbSrc, "main", SQLITE_CHECKPOINT_FULL,
                                 0, 0);
  if( rc ){
    scrubBackupErr(p, "cannot checkpoint the source database");
    return;
  }
  pStmt = scrubBackupPrepare(p, p->dbSrc, "PRAGMA page_size");
  if( pStmt==0 ) return;
  rc = sqlite3_step(pStmt);
  if( rc==SQLITE_ROW ){
    p->szPage = sqlite3_column_int(pStmt, 0);
  }else{
    scrubBackupErr(p, "unable to determine the page size");
  }
  sqlite3_finalize(pStmt);
  if( p->rcErr ) return;
  pStmt = scrubBackupPrepare(p, p->dbSrc, "PRAGMA page_count");
  if( pStmt==0 ) return;
  rc = sqlite3_step(pStmt);
  if( rc==SQLITE_ROW ){
    p->nPage = sqlite3_column_int(pStmt, 0);
  }else{
    scrubBackupErr(p, "unable to determine the size of the source database");
  }
  sqlite3_finalize(pStmt);
  sqlite3_file_control(p->dbSrc, "main", SQLITE_FCNTL_FILE_POINTER, &p->pSrc);
  if( p->pSrc==0 || p->pSrc->pMethods==0 ){
    scrubBackupErr(p, "cannot get the source file handle");
    p->rcErr = SQLITE_ERROR;
  }
}