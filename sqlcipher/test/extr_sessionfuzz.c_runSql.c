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
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,...) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  stderr ; 

__attribute__((used)) static void runSql(sqlite3 *db, const char *zSql){
  int rc;
  char *zErr = 0;
  rc = sqlite3_exec(db, zSql, 0, 0, &zErr);
  if( rc || zErr ){
    fprintf(stderr, "SQL failed: rc=%d zErr=[%s]\n", rc, zErr);
    fprintf(stderr, "SQL: [%s]\n", zSql);
    exit(1);
  }
}