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
typedef  int /*<<< orphan*/  sqlite ;

/* Variables and functions */
 int /*<<< orphan*/  DB_FILE ; 
 scalar_t__ SQLITE_OK ; 
 scalar_t__ all_stop ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  printf (char*,int,int) ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  sqlite3_close (int /*<<< orphan*/ *) ; 
 int sqlite3_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_open (int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  stderr ; 

void *worker(void *workerArg){
  sqlite *db;
  int id = (int)workerArg;
  int rc;
  int cnt = 0;
  fprintf(stderr, "Starting worker %d\n", id);
  while( !all_stop && cnt++<10000 ){
    if( cnt%100==0 ) printf("%d: %d\n", id, cnt);
    while( (sqlite3_open(DB_FILE, &db))!=SQLITE_OK ) sched_yield();
    sqlite3_exec(db, "PRAGMA synchronous=OFF", 0, 0, 0);
    /* integrity_check(db, id); */
    if( all_stop ){ sqlite3_close(db); break; }
    /* fprintf(stderr, "%d: BEGIN\n", id); */
    rc = sqlite3_exec(db, "INSERT INTO t1 VALUES('bogus data')", 0, 0, 0);
    /* fprintf(stderr, "%d: END rc=%d\n", id, rc); */
    sqlite3_close(db);
  }
  fprintf(stderr, "Worker %d finished\n", id);
  return 0;
}