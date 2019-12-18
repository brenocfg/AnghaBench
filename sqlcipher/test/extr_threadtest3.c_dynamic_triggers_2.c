#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int i64 ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_11__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  closedb (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  execsql (TYPE_2__*,TYPE_1__*,char*,int*,...) ; 
 int /*<<< orphan*/  opendb (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 char* sqlite3_mprintf (char*,int,int) ; 
 int /*<<< orphan*/  timetostop (TYPE_2__*) ; 

__attribute__((used)) static char *dynamic_triggers_2(int iTid, void *pArg){
  Error err = {0};                /* Error code and message */
  Sqlite db = {0};                /* SQLite database connection */
  i64 iVal = 0;
  int nInsert = 0;
  int nDelete = 0;

  opendb(&err, &db, "test.db", 0);
  while( !timetostop(&err) ){
    do {
      iVal = (iVal+1)%100;
      execsql(&err, &db, "INSERT INTO t1 VALUES(:iX, :iY+1)", &iVal, &iVal);
      nInsert++;
    } while( iVal );

    do {
      iVal = (iVal+1)%100;
      execsql(&err, &db, "DELETE FROM t1 WHERE x = :iX", &iVal);
      nDelete++;
    } while( iVal );
  }
  closedb(&err, &db);

  print_and_free_err(&err);
  return sqlite3_mprintf("%d inserts, %d deletes", nInsert, nDelete);
}