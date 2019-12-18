#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int tid; int /*<<< orphan*/  db; } ;
typedef  TYPE_1__ WorkerInfo ;

/* Variables and functions */
 int SQLITE_OK ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_SHAREDCACHE ; 
 int /*<<< orphan*/  check_oom (char*) ; 
 int /*<<< orphan*/  exit (int) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ ,char*,char*,int) ; 
 int /*<<< orphan*/  run_sql (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  sqlite3_busy_timeout (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3_free (char*) ; 
 char* sqlite3_mprintf (char*,unsigned char const) ; 
 int sqlite3_open_v2 (char*,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stderr ; 
 int /*<<< orphan*/  worker_trace (TYPE_1__*,char*,char*) ; 

__attribute__((used)) static void worker_open_connection(WorkerInfo *p, int iCnt){
  char *zFile;
  int x;
  int rc;
  static const unsigned char aOrder[6][3] = {
    { 1, 2, 3},
    { 1, 3, 2},
    { 2, 1, 3},
    { 2, 3, 1},
    { 3, 1, 2},
    { 3, 2, 1}
  };
  x = (p->tid + iCnt) % 6;
  zFile = sqlite3_mprintf("tt4-test%d.db", aOrder[x][0]);
  check_oom(zFile);
  worker_trace(p, "open %s", zFile);
  rc = sqlite3_open_v2(zFile, &p->db,
                       SQLITE_OPEN_READWRITE|SQLITE_OPEN_SHAREDCACHE, 0);
  if( rc!=SQLITE_OK ){
    fprintf(stderr, "sqlite_open_v2(%s) failed on thread %d\n",
            zFile, p->tid);
    exit(1);
  }
  sqlite3_free(zFile);
  run_sql(p, "PRAGMA read_uncommitted=ON;");
  sqlite3_busy_timeout(p->db, 10000);
  run_sql(p, "PRAGMA synchronous=OFF;");
  run_sql(p, "ATTACH 'tt4-test%d.db' AS aux1", aOrder[x][1]);
  run_sql(p, "ATTACH 'tt4-test%d.db' AS aux2", aOrder[x][2]);
}