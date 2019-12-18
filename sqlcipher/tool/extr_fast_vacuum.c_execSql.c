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
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,char const*) ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_prepare (int /*<<< orphan*/ *,char const*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  vacuumFinalize (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void execSql(sqlite3 *db, const char *zSql){
  sqlite3_stmt *pStmt;
  if( !zSql ){
    fprintf(stderr, "out of memory!\n");
    exit(1);
  }
  printf("%s;\n", zSql);
  if( SQLITE_OK!=sqlite3_prepare(db, zSql, -1, &pStmt, 0) ){
    fprintf(stderr, "Error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
  sqlite3_step(pStmt);
  vacuumFinalize(pStmt);
}