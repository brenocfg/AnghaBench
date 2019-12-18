#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  zDataTbl; int /*<<< orphan*/  zIdx; int /*<<< orphan*/  zTbl; } ;
struct TYPE_7__ {int rc; TYPE_1__ objiter; int /*<<< orphan*/  nPhaseOneStep; int /*<<< orphan*/  iOalSz; int /*<<< orphan*/  iWalCksum; int /*<<< orphan*/  nProgress; int /*<<< orphan*/  nStep; int /*<<< orphan*/  zStateDb; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbRbu; TYPE_3__* pTargetFd; TYPE_3__* pRbuFd; } ;
typedef  TYPE_2__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_8__ {scalar_t__ iCookie; } ;
typedef  TYPE_3__ rbu_file ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int /*<<< orphan*/  RBU_STATE_CKPT ; 
 int /*<<< orphan*/  RBU_STATE_COOKIE ; 
 int /*<<< orphan*/  RBU_STATE_DATATBL ; 
 int /*<<< orphan*/  RBU_STATE_IDX ; 
 int /*<<< orphan*/  RBU_STATE_OALSZ ; 
 int /*<<< orphan*/  RBU_STATE_PHASEONESTEP ; 
 int /*<<< orphan*/  RBU_STATE_PROGRESS ; 
 int /*<<< orphan*/  RBU_STATE_ROW ; 
 int /*<<< orphan*/  RBU_STATE_STAGE ; 
 int /*<<< orphan*/  RBU_STATE_TBL ; 
 scalar_t__ SQLITE_DONE ; 
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int prepareFreeAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rbuIsVacuum (TYPE_2__*) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void rbuSaveState(sqlite3rbu *p, int eStage){
  if( p->rc==SQLITE_OK || p->rc==SQLITE_DONE ){
    sqlite3_stmt *pInsert = 0;
    rbu_file *pFd = (rbuIsVacuum(p) ? p->pRbuFd : p->pTargetFd);
    int rc;

    assert( p->zErrmsg==0 );
    rc = prepareFreeAndCollectError(p->dbRbu, &pInsert, &p->zErrmsg, 
        sqlite3_mprintf(
          "INSERT OR REPLACE INTO %s.rbu_state(k, v) VALUES "
          "(%d, %d), "
          "(%d, %Q), "
          "(%d, %Q), "
          "(%d, %d), "
          "(%d, %d), "
          "(%d, %lld), "
          "(%d, %lld), "
          "(%d, %lld), "
          "(%d, %lld), "
          "(%d, %Q)  ",
          p->zStateDb,
          RBU_STATE_STAGE, eStage,
          RBU_STATE_TBL, p->objiter.zTbl, 
          RBU_STATE_IDX, p->objiter.zIdx, 
          RBU_STATE_ROW, p->nStep, 
          RBU_STATE_PROGRESS, p->nProgress,
          RBU_STATE_CKPT, p->iWalCksum,
          RBU_STATE_COOKIE, (i64)pFd->iCookie,
          RBU_STATE_OALSZ, p->iOalSz,
          RBU_STATE_PHASEONESTEP, p->nPhaseOneStep,
          RBU_STATE_DATATBL, p->objiter.zDataTbl
      )
    );
    assert( pInsert==0 || rc==SQLITE_OK );

    if( rc==SQLITE_OK ){
      sqlite3_step(pInsert);
      rc = sqlite3_finalize(pInsert);
    }
    if( rc!=SQLITE_OK ) p->rc = rc;
  }
}