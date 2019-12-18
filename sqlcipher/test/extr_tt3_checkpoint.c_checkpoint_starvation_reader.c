#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ i64 ;
struct TYPE_15__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int CHECKPOINT_STARVATION_READMS ; 
 int /*<<< orphan*/  closedb (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ execsql_i64 (TYPE_2__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  opendb (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 int /*<<< orphan*/  sql_script (TYPE_2__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  test_error (TYPE_2__*,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  timetostop (TYPE_2__*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static char *checkpoint_starvation_reader(int iTid, void *pArg){
  Error err = {0};
  Sqlite db = {0};

  opendb(&err, &db, "test.db", 0);
  while( !timetostop(&err) ){
    i64 iCount1, iCount2;
    sql_script(&err, &db, "BEGIN");
    iCount1 = execsql_i64(&err, &db, "SELECT count(x) FROM t1");
    usleep(CHECKPOINT_STARVATION_READMS*1000);
    iCount2 = execsql_i64(&err, &db, "SELECT count(x) FROM t1");
    sql_script(&err, &db, "COMMIT");

    if( iCount1!=iCount2 ){
      test_error(&err, "Isolation failure - %lld %lld", iCount1, iCount2);
    }
  }
  closedb(&err, &db);

  print_and_free_err(&err);
  return 0;
}