#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_14__ {int rc; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  db; int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int /*<<< orphan*/  closedb (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  execsql (TYPE_2__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  opendb (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 char* sqlite3_mprintf (char*) ; 
 int /*<<< orphan*/  sqlite3_prepare_v2 (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite_error (TYPE_2__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  timetostop (TYPE_2__*) ; 

__attribute__((used)) static char *lookaside1_thread_reader(int iTid, void *pArg){
  Error err = {0};                /* Error code and message */
  Sqlite db = {0};                /* SQLite database connection */

  opendb(&err, &db, "test.db", 0);

  while( !timetostop(&err) ){
    sqlite3_stmt *pStmt = 0;
    int rc;

    sqlite3_prepare_v2(db.db, "SELECT 1 FROM t1", -1, &pStmt, 0);
    while( sqlite3_step(pStmt)==SQLITE_ROW ){
      execsql(&err, &db, "SELECT length(x||y||z) FROM t2");
    }
    rc = sqlite3_finalize(pStmt);
    if( err.rc==SQLITE_OK && rc!=SQLITE_OK ){
      sqlite_error(&err, &db, "finalize");
    }
  }

  closedb(&err, &db);
  print_and_free_err(&err);
  return sqlite3_mprintf("ok");
}