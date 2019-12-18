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
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  execSql (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_prepare (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vacuumFinalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void execExecSql(sqlite3 *db, const char *zSql){
  sqlite3_stmt *pStmt;
  int rc;

  printf("%s;\n", zSql);
  rc = sqlite3_prepare(db, zSql, -1, &pStmt, 0);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
  while( SQLITE_ROW==sqlite3_step(pStmt) ){
    execSql(db, (char*)sqlite3_column_text(pStmt, 0));
  }
  vacuumFinalize(pStmt);
}