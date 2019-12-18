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
typedef  int /*<<< orphan*/  sqlite3_str ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  SQLITE_STATIC ; 
 int /*<<< orphan*/  sqlite3_bind_text (int /*<<< orphan*/ *,int,char const*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (int /*<<< orphan*/ *,char*,char const*,char const*,...) ; 

int rename_all_columns_of_table(
  sqlite3 *db,                   /* Database connection */
  const char *zTab,              /* Table whose columns should all be renamed */
  const char *zColPrefix,        /* Prefix for new column names */
  sqlite3_str *pConvert,         /* Append ALTER TABLE statements here */
  sqlite3_str *pUndo             /* SQL to undo the change, if not NULL */
){
  sqlite3_stmt *pStmt;
  int rc;
  int cnt = 0;

  rc = sqlite3_prepare_v2(db,
         "SELECT name FROM pragma_table_info(?1);",
         -1, &pStmt, 0);
  if( rc ) return rc;
  sqlite3_bind_text(pStmt, 1, zTab, -1, SQLITE_STATIC);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    const char *zCol = (const char*)sqlite3_column_text(pStmt, 0);
    cnt++;
    sqlite3_str_appendf(pConvert,
      "ALTER TABLE \"%w\" RENAME COLUMN \"%w\" TO \"%w%d\";\n",
      zTab, zCol, zColPrefix, cnt
    );
    if( pUndo ){
      sqlite3_str_appendf(pUndo,
        "ALTER TABLE \"%w\" RENAME COLUMN \"%w%d\" TO \"%w\";\n",
        zTab, zColPrefix, cnt, zCol
      );
    }
  }
  sqlite3_finalize(pStmt);
  return SQLITE_OK; 
}