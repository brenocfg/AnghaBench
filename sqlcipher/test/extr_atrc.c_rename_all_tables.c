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
 int /*<<< orphan*/  rename_all_columns_of_table (int /*<<< orphan*/ *,char const*,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,int) ; 
 int sqlite3_prepare_v2 (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_str_appendf (int /*<<< orphan*/ *,char*,char const*,char const*) ; 

int rename_all_tables(
  sqlite3 *db,              /* Database connection */
  sqlite3_str *pConvert,    /* Append SQL to do the rename here */
  sqlite3_str *pUndo        /* Append SQL to undo the rename here */
){
  sqlite3_stmt *pStmt;
  int rc;
  int cnt = 0;

  rc = sqlite3_prepare_v2(db,
         "SELECT name FROM sqlite_master WHERE type='table'"
         " AND name NOT LIKE 'sqlite_%';",
         -1, &pStmt, 0);
  if( rc ) return rc;
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    const char *zTab = (const char*)sqlite3_column_text(pStmt, 0);
    char *zNewTab;
    char zPrefix[2];

    zPrefix[0] = (cnt%26) + 'a';
    zPrefix[1] = 0;
    zNewTab = sqlite3_mprintf("tx%d", ++cnt);
    if( pUndo ){
      sqlite3_str_appendf(pUndo,
        "ALTER TABLE \"%s\" RENAME TO \"%w\";\n",
        zNewTab, zTab
      );
    }
    rename_all_columns_of_table(db, zTab, zPrefix, pConvert, pUndo);
    sqlite3_str_appendf(pConvert,
      "ALTER TABLE \"%w\" RENAME TO \"%s\";\n",
      zTab, zNewTab
    );
    sqlite3_free(zNewTab);
  }
  sqlite3_finalize(pStmt);
  return SQLITE_OK;
}