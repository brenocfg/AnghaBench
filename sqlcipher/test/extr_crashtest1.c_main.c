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
 int /*<<< orphan*/  SIGKILL ; 
 int /*<<< orphan*/  do_some_sql (int) ; 
 int fork () ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int rand () ; 
 int /*<<< orphan*/  sched_yield () ; 
 int /*<<< orphan*/  sqlite_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite_exec (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * sqlite_open (char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  usleep (int) ; 
 int /*<<< orphan*/  waitpid (int,int*,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv){
  int i;
  sqlite *db;
  char *zErr;
  int status;
  int parent = getpid();

  unlink("test.db");
  unlink("test.db-journal");
  db = sqlite_open("test.db", 0, &zErr);
  if( db==0 ){
    printf("Cannot initialize: %s\n", zErr);
    return 1;
  }
  sqlite_exec(db, "CREATE TABLE t1(a,b)", 0, 0, 0);
  sqlite_close(db);
  for(i=0; i<10000; i++){
    int pid = fork();
    if( pid==0 ){
      sched_yield();
      do_some_sql(parent);
      return 0;
    }
    printf("test %d, pid=%d\n", i, pid);
    usleep(rand()%10000 + 1000);
    kill(pid, SIGKILL);
    waitpid(pid, &status, 0);
  }
  return 0;
}