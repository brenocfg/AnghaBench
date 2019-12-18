#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_12__ {char const* zSql; scalar_t__ pPreStmt; TYPE_1__* pDb; scalar_t__ pArray; } ;
struct TYPE_11__ {int /*<<< orphan*/ * pStmt; } ;
struct TYPE_10__ {int /*<<< orphan*/  db; int /*<<< orphan*/  interp; scalar_t__ bLegacyPrepare; void* nVMStep; void* nIndex; void* nSort; void* nStep; } ;
typedef  TYPE_1__ SqliteDb ;
typedef  TYPE_2__ SqlPreparedStmt ;
typedef  TYPE_3__ DbEvalContext ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int SQLITE_SCHEMA ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_AUTOINDEX ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_FULLSCAN_STEP ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_SORT ; 
 int /*<<< orphan*/  SQLITE_STMTSTATUS_VM_STEP ; 
 int TCL_BREAK ; 
 int TCL_ERROR ; 
 int TCL_OK ; 
 int /*<<< orphan*/  Tcl_NewStringObj (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  Tcl_SetObjResult (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dbEvalRowInfo (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int dbPrepareAndBind (TYPE_1__*,char*,char**,scalar_t__*) ; 
 int /*<<< orphan*/  dbReleaseColumnNames (TYPE_3__*) ; 
 int /*<<< orphan*/  dbReleaseStmt (TYPE_1__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 
 void* sqlite3_stmt_status (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int dbEvalStep(DbEvalContext *p){
  const char *zPrevSql = 0;       /* Previous value of p->zSql */

  while( p->zSql[0] || p->pPreStmt ){
    int rc;
    if( p->pPreStmt==0 ){
      zPrevSql = (p->zSql==zPrevSql ? 0 : p->zSql);
      rc = dbPrepareAndBind(p->pDb, p->zSql, &p->zSql, &p->pPreStmt);
      if( rc!=TCL_OK ) return rc;
    }else{
      int rcs;
      SqliteDb *pDb = p->pDb;
      SqlPreparedStmt *pPreStmt = p->pPreStmt;
      sqlite3_stmt *pStmt = pPreStmt->pStmt;

      rcs = sqlite3_step(pStmt);
      if( rcs==SQLITE_ROW ){
        return TCL_OK;
      }
      if( p->pArray ){
        dbEvalRowInfo(p, 0, 0);
      }
      rcs = sqlite3_reset(pStmt);

      pDb->nStep = sqlite3_stmt_status(pStmt,SQLITE_STMTSTATUS_FULLSCAN_STEP,1);
      pDb->nSort = sqlite3_stmt_status(pStmt,SQLITE_STMTSTATUS_SORT,1);
      pDb->nIndex = sqlite3_stmt_status(pStmt,SQLITE_STMTSTATUS_AUTOINDEX,1);
      pDb->nVMStep = sqlite3_stmt_status(pStmt,SQLITE_STMTSTATUS_VM_STEP,1);
      dbReleaseColumnNames(p);
      p->pPreStmt = 0;

      if( rcs!=SQLITE_OK ){
        /* If a run-time error occurs, report the error and stop reading
        ** the SQL.  */
        dbReleaseStmt(pDb, pPreStmt, 1);
#if SQLITE_TEST
        if( p->pDb->bLegacyPrepare && rcs==SQLITE_SCHEMA && zPrevSql ){
          /* If the runtime error was an SQLITE_SCHEMA, and the database
          ** handle is configured to use the legacy sqlite3_prepare()
          ** interface, retry prepare()/step() on the same SQL statement.
          ** This only happens once. If there is a second SQLITE_SCHEMA
          ** error, the error will be returned to the caller. */
          p->zSql = zPrevSql;
          continue;
        }
#endif
        Tcl_SetObjResult(pDb->interp,
                         Tcl_NewStringObj(sqlite3_errmsg(pDb->db), -1));
        return TCL_ERROR;
      }else{
        dbReleaseStmt(pDb, pPreStmt, 0);
      }
    }
  }

  /* Finished */
  return TCL_BREAK;
}