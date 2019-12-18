#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {scalar_t__ rc; int /*<<< orphan*/  member_0; } ;
struct TYPE_12__ {int /*<<< orphan*/  member_0; } ;
typedef  TYPE_1__ Sqlite ;
typedef  TYPE_2__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_BUSY ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  clear_error (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedb (TYPE_2__*,TYPE_1__*) ; 
 int /*<<< orphan*/  execsql (TYPE_2__*,TYPE_1__*,char*) ; 
 int /*<<< orphan*/  opendb (TYPE_2__*,TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_2__*) ; 
 char* sqlite3_mprintf (char*,int) ; 
 int /*<<< orphan*/  timetostop (TYPE_2__*) ; 
 int /*<<< orphan*/  usleep (int) ; 

__attribute__((used)) static char *walthread1_ckpt_thread(int iTid, void *pArg){
  Error err = {0};                /* Error code and message */
  Sqlite db = {0};                /* SQLite database connection */
  int nCkpt = 0;                  /* Checkpoints so far */

  opendb(&err, &db, "test.db", 0);
  while( !timetostop(&err) ){
    usleep(500*1000);
    execsql(&err, &db, "PRAGMA wal_checkpoint");
    if( err.rc==SQLITE_OK ) nCkpt++;
    clear_error(&err, SQLITE_BUSY);
  }
  closedb(&err, &db);

  print_and_free_err(&err);
  return sqlite3_mprintf("%d checkpoints", nCkpt);
}