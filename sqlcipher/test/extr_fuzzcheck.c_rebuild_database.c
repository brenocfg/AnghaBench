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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  fatalError (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,char*) ; 

__attribute__((used)) static void rebuild_database(sqlite3 *db, int dbSqlOnly){
  int rc;
  char *zSql;
  zSql = sqlite3_mprintf(
     "BEGIN;\n"
     "CREATE TEMP TABLE dbx AS SELECT DISTINCT dbcontent FROM db;\n"
     "DELETE FROM db;\n"
     "INSERT INTO db(dbid, dbcontent) "
        " SELECT NULL, dbcontent FROM dbx ORDER BY 2;\n"
     "DROP TABLE dbx;\n"
     "CREATE TEMP TABLE sx AS SELECT DISTINCT sqltext FROM xsql %s;\n"
     "DELETE FROM xsql;\n"
     "INSERT INTO xsql(sqlid,sqltext) "
        " SELECT NULL, sqltext FROM sx ORDER BY 2;\n"
     "DROP TABLE sx;\n"
     "COMMIT;\n"
     "PRAGMA page_size=1024;\n"
     "VACUUM;\n",
     dbSqlOnly ? " WHERE isdbsql(sqltext)" : ""
  );
  rc = sqlite3_exec(db, zSql, 0, 0, 0);
  sqlite3_free(zSql);
  if( rc ) fatalError("cannot rebuild: %s", sqlite3_errmsg(db));
}