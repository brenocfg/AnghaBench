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
struct TYPE_18__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Threadset ;
struct TYPE_20__ {scalar_t__ rc; int /*<<< orphan*/  member_0; } ;
struct TYPE_19__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_2__ Sqlite ;
typedef  TYPE_3__ Error ;

/* Variables and functions */
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  closedb (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  filecopy (TYPE_3__*,char*,char*) ; 
 scalar_t__ filesize (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  join_all_threads (TYPE_3__*,TYPE_1__*) ; 
 int /*<<< orphan*/  launch_thread (TYPE_3__*,TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  opendb (TYPE_3__*,TYPE_2__*,char*,int) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_3__*) ; 
 int /*<<< orphan*/  printf (char*,int) ; 
 int /*<<< orphan*/  setstoptime (TYPE_3__*,int) ; 
 int /*<<< orphan*/  sql_script (TYPE_3__*,TYPE_2__*,char*) ; 
 int /*<<< orphan*/  walthread5_thread ; 

__attribute__((used)) static void walthread5(int nMs){
  Error err = {0};
  Sqlite db = {0};
  Threadset threads = {0};

  opendb(&err, &db, "test.db", 1);
  sql_script(&err, &db, 
      "PRAGMA wal_autocheckpoint = 0;"
      "PRAGMA page_size = 1024;"
      "PRAGMA journal_mode = WAL;"
      "CREATE TABLE t1(x);"
      "BEGIN;"
      "INSERT INTO t1 VALUES(randomblob(900));"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*     2 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*     4 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*     8 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*    16 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*    32 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*    64 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*   128 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*   256 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*   512 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*  1024 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*  2048 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*  4096 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /*  8192 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /* 16384 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /* 32768 */"
      "INSERT INTO t1 SELECT randomblob(900) FROM t1;      /* 65536 */"
      "COMMIT;"
  );
  filecopy(&err, "test.db", "test_sv.db");
  filecopy(&err, "test.db-wal", "test_sv.db-wal");
  closedb(&err, &db);

  filecopy(&err, "test_sv.db", "test.db");
  filecopy(&err, "test_sv.db-wal", "test.db-wal");

  if( err.rc==SQLITE_OK ){
    printf("  WAL file is %d bytes,", (int)filesize(&err,"test.db-wal"));
    printf(" DB file is %d.\n", (int)filesize(&err,"test.db"));
  }

  setstoptime(&err, nMs);
  launch_thread(&err, &threads, walthread5_thread, 0);
  launch_thread(&err, &threads, walthread5_thread, 0);
  launch_thread(&err, &threads, walthread5_thread, 0);
  launch_thread(&err, &threads, walthread5_thread, 0);
  launch_thread(&err, &threads, walthread5_thread, 0);
  join_all_threads(&err, &threads);

  if( err.rc==SQLITE_OK ){
    printf("  WAL file is %d bytes,", (int)filesize(&err,"test.db-wal"));
    printf(" DB file is %d.\n", (int)filesize(&err,"test.db"));
  }

  print_and_free_err(&err);
}