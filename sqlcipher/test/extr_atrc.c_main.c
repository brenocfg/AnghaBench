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
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rename_all_tables (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int sqlite3_open (char*,int /*<<< orphan*/ **) ; 
 char* sqlite3_str_finish (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * sqlite3_str_new (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stderr ; 

int main(int argc, char **argv){
  sqlite3 *db;
  int rc;
  sqlite3_str *pConvert;
  sqlite3_str *pUndo;
  char *zDbName;
  char *zSql1, *zSql2;
  if( argc!=2 ){
    fprintf(stderr, "Usage: %s DATABASE\n", argv[0]);
  }
  zDbName = argv[1];
  rc = sqlite3_open(zDbName, &db);
  if( rc ){
    fprintf(stderr, "sqlite3_open() returns %d\n", rc);
    return 1;
  }
  pConvert = sqlite3_str_new(db);
  pUndo = sqlite3_str_new(db);
  rename_all_tables(db, pConvert, pUndo);
  zSql1 = sqlite3_str_finish(pConvert);
  zSql2 = sqlite3_str_finish(pUndo);
  sqlite3_close(db);
  printf("BEGIN;\n");
  printf("%s", zSql1);
  sqlite3_free(zSql1);
  printf(".schema --indent\n");
  printf("PRAGMA integrity_check;\n");
  printf("%s", zSql2);
  sqlite3_free(zSql2);
  printf("PRAGMA integrity_check;\n");
  printf("ROLLBACK;\n");
  return 0; 
}