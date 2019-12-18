#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {scalar_t__ rc; int /*<<< orphan*/  member_0; } ;
struct TYPE_14__ {int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* xProc ) (TYPE_3__*,TYPE_2__*,int) ;int /*<<< orphan*/  zDb; } ;
typedef  TYPE_1__ Stress2Ctx ;
typedef  TYPE_2__ Sqlite ;
typedef  TYPE_3__ Error ;

/* Variables and functions */
 int /*<<< orphan*/  SQLITE_LOCKED ; 
 scalar_t__ SQLITE_OK ; 
 int STRESS2_TABCNT ; 
 int /*<<< orphan*/  clear_error (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  closedb (TYPE_3__*,TYPE_2__*) ; 
 int /*<<< orphan*/  opendb (TYPE_3__*,TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  print_and_free_err (TYPE_3__*) ; 
 char* sqlite3_mprintf (char*,int,int) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,TYPE_2__*,int) ; 
 int /*<<< orphan*/  timetostop (TYPE_3__*) ; 

__attribute__((used)) static char *stress2_thread_wrapper(int iTid, void *pArg){
  Stress2Ctx *pCtx = (Stress2Ctx*)pArg;
  Error err = {0};                /* Error code and message */
  Sqlite db = {0};                /* SQLite database connection */
  int i1 = 0;
  int i2 = 0;

  while( !timetostop(&err) ){
    int cnt;
    opendb(&err, &db, pCtx->zDb, 0);
    for(cnt=0; err.rc==SQLITE_OK && cnt<STRESS2_TABCNT; cnt++){
      pCtx->xProc(&err, &db, i1);
      i2 += (err.rc==SQLITE_OK);
      clear_error(&err, SQLITE_LOCKED);
      i1++;
    }
    closedb(&err, &db);
  }

  print_and_free_err(&err);
  return sqlite3_mprintf("ok %d/%d", i2, i1);
}