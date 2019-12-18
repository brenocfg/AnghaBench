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
typedef  int /*<<< orphan*/  sqlite3_int64 ;
typedef  int /*<<< orphan*/  Fts3Table ;

/* Variables and functions */
 int FTS_CORRUPT_VTAB ; 
 scalar_t__ SQLITE_BLOB ; 
 int SQLITE_OK ; 
 int SQLITE_ROW ; 
 int /*<<< orphan*/  SQL_SELECT_DOCSIZE ; 
 int fts3SqlStmt (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_bind_int64 (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int sqlite3_reset (int /*<<< orphan*/ *) ; 
 int sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int fts3SelectDocsize(
  Fts3Table *pTab,                /* FTS3 table handle */
  sqlite3_int64 iDocid,           /* Docid to bind for SQL_SELECT_DOCSIZE */
  sqlite3_stmt **ppStmt           /* OUT: Statement handle */
){
  sqlite3_stmt *pStmt = 0;        /* Statement requested from fts3SqlStmt() */
  int rc;                         /* Return code */

  rc = fts3SqlStmt(pTab, SQL_SELECT_DOCSIZE, &pStmt, 0);
  if( rc==SQLITE_OK ){
    sqlite3_bind_int64(pStmt, 1, iDocid);
    rc = sqlite3_step(pStmt);
    if( rc!=SQLITE_ROW || sqlite3_column_type(pStmt, 0)!=SQLITE_BLOB ){
      rc = sqlite3_reset(pStmt);
      if( rc==SQLITE_OK ) rc = FTS_CORRUPT_VTAB;
      pStmt = 0;
    }else{
      rc = SQLITE_OK;
    }
  }

  *ppStmt = pStmt;
  return rc;
}