#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {int rc; scalar_t__ eStage; int /*<<< orphan*/  dbMain; int /*<<< orphan*/  dbRbu; TYPE_1__* pTargetFd; } ;
typedef  TYPE_3__ sqlite3rbu ;
struct TYPE_12__ {TYPE_2__* pMethods; } ;
typedef  TYPE_4__ sqlite3_file ;
struct TYPE_10__ {int (* xSync ) (TYPE_4__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_9__ {TYPE_4__* pReal; } ;

/* Variables and functions */
 scalar_t__ RBU_STAGE_CKPT ; 
 scalar_t__ RBU_STAGE_DONE ; 
 scalar_t__ RBU_STAGE_OAL ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_SYNC_NORMAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ rbuIsVacuum (TYPE_3__*) ; 
 int /*<<< orphan*/  rbuSaveState (TYPE_3__*,scalar_t__) ; 
 int sqlite3_exec (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_4__*,int /*<<< orphan*/ ) ; 

int sqlite3rbu_savestate(sqlite3rbu *p){
  int rc = p->rc;
  if( rc==SQLITE_DONE ) return SQLITE_OK;

  assert( p->eStage>=RBU_STAGE_OAL && p->eStage<=RBU_STAGE_DONE );
  if( p->eStage==RBU_STAGE_OAL ){
    assert( rc!=SQLITE_DONE );
    if( rc==SQLITE_OK ) rc = sqlite3_exec(p->dbMain, "COMMIT", 0, 0, 0);
  }

  /* Sync the db file */
  if( rc==SQLITE_OK && p->eStage==RBU_STAGE_CKPT ){
    sqlite3_file *pDb = p->pTargetFd->pReal;
    rc = pDb->pMethods->xSync(pDb, SQLITE_SYNC_NORMAL);
  }

  p->rc = rc;
  rbuSaveState(p, p->eStage);
  rc = p->rc;

  if( p->eStage==RBU_STAGE_OAL ){
    assert( rc!=SQLITE_DONE );
    if( rc==SQLITE_OK ) rc = sqlite3_exec(p->dbRbu, "COMMIT", 0, 0, 0);
    if( rc==SQLITE_OK ){ 
      const char *zBegin = rbuIsVacuum(p) ? "BEGIN" : "BEGIN IMMEDIATE";
      rc = sqlite3_exec(p->dbRbu, zBegin, 0, 0, 0);
    }
    if( rc==SQLITE_OK ) rc = sqlite3_exec(p->dbMain, "BEGIN IMMEDIATE", 0, 0,0);
  }

  p->rc = rc;
  return rc;
}