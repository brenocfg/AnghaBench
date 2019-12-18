#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  dbMain; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_value ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3_context ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  assert (int) ; 
 int prepareFreeAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,char**,int /*<<< orphan*/ ) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ ) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_result_error (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  sqlite3_result_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_user_data (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_value_text (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuIndexCntFunc(
  sqlite3_context *pCtx, 
  int nVal,
  sqlite3_value **apVal
){
  sqlite3rbu *p = (sqlite3rbu*)sqlite3_user_data(pCtx);
  sqlite3_stmt *pStmt = 0;
  char *zErrmsg = 0;
  int rc;

  assert( nVal==1 );
  
  rc = prepareFreeAndCollectError(p->dbMain, &pStmt, &zErrmsg, 
      sqlite3_mprintf("SELECT count(*) FROM sqlite_master "
        "WHERE type='index' AND tbl_name = %Q", sqlite3_value_text(apVal[0]))
  );
  if( rc!=SQLITE_OK ){
    sqlite3_result_error(pCtx, zErrmsg, -1);
  }else{
    int nIndex = 0;
    if( SQLITE_ROW==sqlite3_step(pStmt) ){
      nIndex = sqlite3_column_int(pStmt, 0);
    }
    rc = sqlite3_finalize(pStmt);
    if( rc==SQLITE_OK ){
      sqlite3_result_int(pCtx, nIndex);
    }else{
      sqlite3_result_error(pCtx, sqlite3_errmsg(p->dbMain), -1);
    }
  }

  sqlite3_free(zErrmsg);
}