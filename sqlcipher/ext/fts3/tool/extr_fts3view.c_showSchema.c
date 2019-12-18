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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/ * prepare (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void showSchema(sqlite3 *db, const char *zTab){
  sqlite3_stmt *pStmt;
  pStmt = prepare(db,
            "SELECT sql FROM sqlite_master"
            " WHERE name LIKE '%q%%'"
            " ORDER BY 1",
            zTab);
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    printf("%s;\n", sqlite3_column_text(pStmt, 0));
  }
  sqlite3_finalize(pStmt);
  pStmt = prepare(db, "PRAGMA page_size");
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    printf("PRAGMA page_size=%s;\n", sqlite3_column_text(pStmt, 0));
  }
  sqlite3_finalize(pStmt);
  pStmt = prepare(db, "PRAGMA journal_mode");
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    printf("PRAGMA journal_mode=%s;\n", sqlite3_column_text(pStmt, 0));
  }
  sqlite3_finalize(pStmt);
  pStmt = prepare(db, "PRAGMA auto_vacuum");
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    const char *zType = "???";
    switch( sqlite3_column_int(pStmt, 0) ){
      case 0:  zType = "OFF";         break;
      case 1:  zType = "FULL";        break;
      case 2:  zType = "INCREMENTAL"; break;
    }
    printf("PRAGMA auto_vacuum=%s;\n", zType);
  }
  sqlite3_finalize(pStmt);
  pStmt = prepare(db, "PRAGMA encoding");
  while( sqlite3_step(pStmt)==SQLITE_ROW ){
    printf("PRAGMA encoding=%s;\n", sqlite3_column_text(pStmt, 0));
  }
  sqlite3_finalize(pStmt);
}