#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Threadset ;
struct TYPE_22__ {scalar_t__ eMode; int nMaxFrame; } ;
struct TYPE_21__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_20__ {int /*<<< orphan*/  db; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ Sqlite ;
typedef  TYPE_3__ Error ;
typedef  TYPE_4__ CheckpointStarvationCtx ;

/* Variables and functions */
 int CHECKPOINT_STARVATION_READMS ; 
 scalar_t__ SQLITE_CHECKPOINT_PASSIVE ; 
 int /*<<< orphan*/  checkpoint_starvation_reader ; 
 int /*<<< orphan*/  checkpoint_starvation_walhook ; 
 int /*<<< orphan*/  closedb (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  join_all_threads (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  launch_thread (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opendb (TYPE_3__*,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 
 int /*<<< orphan*/  setstoptime (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sql_script (TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sqlite3_wal_hook (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  timetostop (TYPE_3__*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static void checkpoint_starvation_main(int nMs, CheckpointStarvationCtx *p){
  Error err = {0};
  Sqlite db = {0};
  Threadset threads = {0};
  int nInsert = 0;
  int i;

  opendb(&err, &db, "test.db", 1);
  sql_script(&err, &db, 
      "PRAGMA page_size = 1024;"
      "PRAGMA journal_mode = WAL;"
      "CREATE TABLE t1(x);"
  );

  setstoptime(&err, nMs);

  for(i=0; i<4; i++){
    launch_thread(&err, &threads, checkpoint_starvation_reader, 0);
    usleep(CHECKPOINT_STARVATION_READMS*1000/4);
  }

  sqlite3_wal_hook(db.db, checkpoint_starvation_walhook, (void *)p);
  while( !timetostop(&err) ){
    sql_script(&err, &db, "INSERT INTO t1 VALUES(randomblob(1200))");
    nInsert++;
  }

  printf(" Checkpoint mode  : %s\n",
      p->eMode==SQLITE_CHECKPOINT_PASSIVE ? "PASSIVE" : "RESTART"
  );
  printf(" Peak WAL         : %d frames\n", p->nMaxFrame);
  printf(" Transaction count: %d transactions\n", nInsert);

  join_all_threads(&err, &threads);
  closedb(&err, &db);
  print_and_free_err(&err);
}