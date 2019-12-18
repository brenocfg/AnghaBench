#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;

/* Variables and functions */
 int SQLITE_ERROR ; 
 int SQLITE_NOMEM ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  printf (char*,int,int,int,char const*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  sqlite3_db_handle (int /*<<< orphan*/ *) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char const*) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 char* sqlite3_sql (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

int printExplainQueryPlan(sqlite3_stmt *pStmt){
  const char *zSql;               /* Input SQL */
  char *zExplain;                 /* SQL with EXPLAIN QUERY PLAN prepended */
  sqlite3_stmt *pExplain;         /* Compiled EXPLAIN QUERY PLAN command */
  int rc;                         /* Return code from sqlite3_prepare_v2() */

  zSql = sqlite3_sql(pStmt);
  if( zSql==0 ) return SQLITE_ERROR;

  zExplain = sqlite3_mprintf("EXPLAIN QUERY PLAN %s", zSql);
  if( zExplain==0 ) return SQLITE_NOMEM;

  rc = sqlite3_prepare_v2(sqlite3_db_handle(pStmt), zExplain, -1, &pExplain, 0);
  sqlite3_free(zExplain);
  if( rc!=SQLITE_OK ) return rc;

  while( SQLITE_ROW==sqlite3_step(pExplain) ){
    int iSelectid = sqlite3_column_int(pExplain, 0);
    int iOrder = sqlite3_column_int(pExplain, 1);
    int iFrom = sqlite3_column_int(pExplain, 2);
    const char *zDetail = (const char *)sqlite3_column_text(pExplain, 3);

    printf("%d %d %d %s\n", iSelectid, iOrder, iFrom, zDetail);
  }

  return sqlite3_finalize(pExplain);
}