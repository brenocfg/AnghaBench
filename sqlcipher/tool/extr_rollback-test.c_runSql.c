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
 int /*<<< orphan*/  execCallback ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*) ; 
 scalar_t__ nReply ; 
 char* sqlite3_errmsg (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void runSql(sqlite3 *db, const char *zSql){
  char *zErr = 0;
  int rc;
  nReply = 0;
  rc = sqlite3_exec(db, zSql, execCallback, 0, &zErr);
  if( zErr ){
    fprintf(stderr, "SQL error: %s\n", zErr);
    exit(1);
  }
  if( rc ){
    fprintf(stderr, "SQL error: %s\n", sqlite3_errmsg(db));
    exit(1);
  }
}