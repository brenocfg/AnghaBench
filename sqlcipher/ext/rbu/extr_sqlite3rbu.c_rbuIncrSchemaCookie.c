#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ rc; int /*<<< orphan*/ * dbMain; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/ * dbRbu; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 scalar_t__ prepareAndCollectError (int /*<<< orphan*/ *,int /*<<< orphan*/ **,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  rbuFinalize (TYPE_1__*,int /*<<< orphan*/ *) ; 
 scalar_t__ rbuIsVacuum (TYPE_1__*) ; 
 int /*<<< orphan*/  rbuMPrintfExec (TYPE_1__*,int /*<<< orphan*/ *,char*,int) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuIncrSchemaCookie(sqlite3rbu *p){
  if( p->rc==SQLITE_OK ){
    sqlite3 *dbread = (rbuIsVacuum(p) ? p->dbRbu : p->dbMain);
    int iCookie = 1000000;
    sqlite3_stmt *pStmt;

    p->rc = prepareAndCollectError(dbread, &pStmt, &p->zErrmsg, 
        "PRAGMA schema_version"
    );
    if( p->rc==SQLITE_OK ){
      /* Coverage: it may be that this sqlite3_step() cannot fail. There
      ** is already a transaction open, so the prepared statement cannot
      ** throw an SQLITE_SCHEMA exception. The only database page the
      ** statement reads is page 1, which is guaranteed to be in the cache.
      ** And no memory allocations are required.  */
      if( SQLITE_ROW==sqlite3_step(pStmt) ){
        iCookie = sqlite3_column_int(pStmt, 0);
      }
      rbuFinalize(p, pStmt);
    }
    if( p->rc==SQLITE_OK ){
      rbuMPrintfExec(p, p->dbMain, "PRAGMA schema_version = %d", iCookie+1);
    }
  }
}