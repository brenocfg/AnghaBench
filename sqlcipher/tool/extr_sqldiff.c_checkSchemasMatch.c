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
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/ * db_prepare (char*,char const*,char const*) ; 
 int /*<<< orphan*/  runtimeError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  safeId (char const*) ; 
 scalar_t__ sqlite3_column_int (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_finalize (int /*<<< orphan*/ *) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void checkSchemasMatch(const char *zTab){
  sqlite3_stmt *pStmt = db_prepare(
      "SELECT A.sql=B.sql FROM main.sqlite_master A, aux.sqlite_master B"
      " WHERE A.name=%Q AND B.name=%Q", zTab, zTab
  );
  if( SQLITE_ROW==sqlite3_step(pStmt) ){
    if( sqlite3_column_int(pStmt,0)==0 ){
      runtimeError("schema changes for table %s", safeId(zTab));
    }
  }else{
    runtimeError("table %s missing from one or both databases", safeId(zTab));
  }
  sqlite3_finalize(pStmt);
}