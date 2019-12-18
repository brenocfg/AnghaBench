#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  aTask ;
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Threadset ;
struct TYPE_20__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ Sqlite ;
typedef  TYPE_3__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  closedb (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  join_all_threads (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  launch_thread (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  opendb (TYPE_3__*,TYPE_2__*,char const*,int) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_3__*) ; 
 int /*<<< orphan*/  setstoptime (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sql_script (TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sqlite3_enable_shared_cache (int) ; 
 int /*<<< orphan*/  stress2_launch_thread_loop (TYPE_3__*,TYPE_1__*,char const*,void (*) (Error*,Sqlite*,int)) ; 
 int /*<<< orphan*/  stress2_workload1 ; 
 int /*<<< orphan*/  stress2_workload10 ; 
 int /*<<< orphan*/  stress2_workload11 ; 
 int /*<<< orphan*/  stress2_workload14 ; 
 int /*<<< orphan*/  stress2_workload17 ; 
 int /*<<< orphan*/  stress2_workload19 ; 
 int /*<<< orphan*/  stress2_workload2 ; 
 int /*<<< orphan*/  stress2_workload3 ; 
 int /*<<< orphan*/  stress2_workload4 ; 
 int /*<<< orphan*/  stress2_workload5 ; 
 int /*<<< orphan*/  stress2_workload6 ; 
 int /*<<< orphan*/  stress2_workload7 ; 
 int /*<<< orphan*/  stress2_workload8 ; 
 int /*<<< orphan*/  stress2_workload9 ; 

__attribute__((used)) static void stress2(int nMs){
  struct Stress2Task {
    void (*x)(Error*,Sqlite*,int);
  } aTask[] = {
    { stress2_workload1 },
    { stress2_workload2 },
    { stress2_workload3 },
    { stress2_workload4 },
    { stress2_workload5 },
    { stress2_workload6 },
    { stress2_workload7 },
    { stress2_workload8 },
    { stress2_workload9 },
    { stress2_workload10 },
    { stress2_workload11 },
    { stress2_workload14 },
    { stress2_workload17 },
  };
  const char *zDb = "test.db";

  int i;
  Error err = {0};
  Sqlite db = {0};
  Threadset threads = {0};

  /* To make sure the db file is empty before commencing */
  opendb(&err, &db, zDb, 1);
  sql_script(&err, &db, 
      "CREATE TABLE IF NOT EXISTS t0(x PRIMARY KEY, y, z);"
      "CREATE INDEX IF NOT EXISTS i0 ON t0(y);"
  );
  closedb(&err, &db);

  setstoptime(&err, nMs);
  sqlite3_enable_shared_cache(1);

  for(i=0; i<sizeof(aTask)/sizeof(aTask[0]); i++){
    stress2_launch_thread_loop(&err, &threads, zDb, aTask[i].x);
  }
  launch_thread(&err, &threads, stress2_workload19, (void*)zDb);
  launch_thread(&err, &threads, stress2_workload19, (void*)zDb);

  join_all_threads(&err, &threads);
  sqlite3_enable_shared_cache(0);
  print_and_free_err(&err);
}