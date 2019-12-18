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
 int SQLITE_CORRUPT ; 
 int SQLITE_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  exit (int) ; 
 int getpid () ; 
 int /*<<< orphan*/  kill (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  rand () ; 
 int sqlite_exec_printf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/ * sqlite_open (char*,int /*<<< orphan*/ ,char**) ; 
 int /*<<< orphan*/  srand (int) ; 
 scalar_t__ strcmp (char*,char*) ; 
 int /*<<< orphan*/  system (char*) ; 
 int /*<<< orphan*/  unlink (char*) ; 

__attribute__((used)) static void do_some_sql(int parent){
  char *zErr;
  int rc = SQLITE_OK;
  sqlite *db;
  int cnt = 0;
  static char zBig[] = 
    "-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ"
    "-abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";

  if( access("./test.db-journal",0)==0 ){
    /*printf("pid %d: journal exists.  rollback will be required\n",getpid());*/    unlink("test.db-saved");
    system("cp test.db test.db-saved");
    unlink("test.db-journal-saved");
    system("cp test.db-journal test.db-journal-saved");
  }
  db = sqlite_open("./test.db", 0, &zErr);
  if( db==0 ){
    printf("ERROR: %s\n", zErr);
    if( strcmp(zErr,"database disk image is malformed")==0 ){
      kill(parent, SIGKILL);
    }
    exit(1);
  }
  srand(getpid());
  while( rc==SQLITE_OK ){
    cnt++;
    rc = sqlite_exec_printf(db, 
       "INSERT INTO t1 VALUES(%d,'%d%s')", 0, 0, &zErr,
       rand(), rand(), zBig);
  }
  if( rc!=SQLITE_OK ){
    printf("ERROR #%d: %s\n", rc, zErr);
    if( rc==SQLITE_CORRUPT ){
      kill(parent, SIGKILL);
    }
  }
  printf("pid %d: cnt=%d\n", getpid(), cnt);
}