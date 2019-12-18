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
typedef  int /*<<< orphan*/  sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3 ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_FCNTL_VFSNAME ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  sqlite3_file_control (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 int /*<<< orphan*/ * sqlite3rbu_db (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stdout ; 

void report_rbu_vfs(sqlite3rbu *pRbu){
  sqlite3 *db = sqlite3rbu_db(pRbu, 0);
  if( db ){
    char *zName = 0;
    sqlite3_file_control(db, "main", SQLITE_FCNTL_VFSNAME, &zName);
    if( zName ){
      fprintf(stdout, "using vfs \"%s\"\n", zName);
    }else{
      fprintf(stdout, "vfs name not available\n");
    }
    sqlite3_free(zName);
  }
}