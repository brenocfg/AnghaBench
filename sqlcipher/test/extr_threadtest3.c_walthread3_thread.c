#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_16__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int PTR2INT (void*) ; 
 scalar_t__ WALTHREAD3_NTHREAD ; 
 int /*<<< orphan*/  closedb (TYPE_2__*,TYPE_1__*) ; 
 int execsql_i64 (TYPE_2__*,TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  integrity_check (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  opendb (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 int /*<<< orphan*/  sql_script (TYPE_2__*,TYPE_1__*,char*) ; 
 int timetostop (TYPE_2__*) ; 

__attribute__((used)) static char *walthread3_thread(int iTid, void *pArg){
  Error err = {0};                /* Error code and message */
  Sqlite db = {0};                /* SQLite database connection */
  i64 iNextWrite;                 /* Next value this thread will write */
  int iArg = PTR2INT(pArg);

  opendb(&err, &db, "test.db", 0);
  sql_script(&err, &db, "PRAGMA wal_autocheckpoint = 10");

  iNextWrite = iArg+1;
  while( 1 ){
    i64 sum1;
    i64 sum2;
    int stop = 0;                 /* True to stop executing (test timed out) */

    while( 0==(stop = timetostop(&err)) ){
      i64 iMax = execsql_i64(&err, &db, "SELECT max(cnt) FROM t1");
      if( iMax+1==iNextWrite ) break;
    }
    if( stop ) break;

    sum1 = execsql_i64(&err, &db, "SELECT sum(cnt) FROM t1");
    sum2 = execsql_i64(&err, &db, "SELECT sum(sum1) FROM t1");
    execsql_i64(&err, &db, 
        "INSERT INTO t1 VALUES(:iNextWrite, :iSum1, :iSum2)",
        &iNextWrite, &sum1, &sum2
    );
    integrity_check(&err, &db);

    iNextWrite += WALTHREAD3_NTHREAD;
  }

  closedb(&err, &db);
  print_and_free_err(&err);
  return 0;
}