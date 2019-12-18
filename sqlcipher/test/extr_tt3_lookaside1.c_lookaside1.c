#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Threadset ;
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_17__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ Sqlite ;
typedef  TYPE_3__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  closedb (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  join_all_threads (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  launch_thread (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lookaside1_thread_reader ; 
 int /*<<< orphan*/  lookaside1_thread_writer ; 
 int /*<<< orphan*/  opendb (TYPE_3__*,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_3__*) ; 
 int /*<<< orphan*/  setstoptime (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sql_script (TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  sqlite3_enable_shared_cache (int) ; 

__attribute__((used)) static void lookaside1(int nMs){
  Error err = {0};
  Sqlite db = {0};
  Threadset threads = {0};

  opendb(&err, &db, "test.db", 1);
  sql_script(&err, &db, 
     "CREATE TABLE t1(x PRIMARY KEY) WITHOUT ROWID;"
     "WITH data(x,y) AS ("
     "  SELECT 1, quote(randomblob(750)) UNION ALL "
     "  SELECT x*2, y||y FROM data WHERE x<5) "
     "INSERT INTO t1 SELECT y FROM data;"

     "CREATE TABLE t3(x PRIMARY KEY,i) WITHOUT ROWID;"
     "INSERT INTO t3 VALUES(1, 1);"

     "CREATE TABLE t2(x,y,z);"
     "INSERT INTO t2 VALUES(randomblob(50), randomblob(50), randomblob(50));"
  );
  closedb(&err, &db);

  setstoptime(&err, nMs);

  sqlite3_enable_shared_cache(1);
  launch_thread(&err, &threads, lookaside1_thread_reader, 0);
  launch_thread(&err, &threads, lookaside1_thread_reader, 0);
  launch_thread(&err, &threads, lookaside1_thread_reader, 0);
  launch_thread(&err, &threads, lookaside1_thread_reader, 0);
  launch_thread(&err, &threads, lookaside1_thread_reader, 0);
  launch_thread(&err, &threads, lookaside1_thread_writer, 0);
  join_all_threads(&err, &threads);
  sqlite3_enable_shared_cache(0);
  print_and_free_err(&err);
}