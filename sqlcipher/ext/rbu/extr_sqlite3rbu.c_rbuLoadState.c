#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  void* u32 ;
struct TYPE_6__ {int rc; int /*<<< orphan*/  zStateDb; int /*<<< orphan*/  zErrmsg; int /*<<< orphan*/  dbRbu; } ;
typedef  TYPE_1__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_stmt ;
struct TYPE_7__ {int eStage; int nRow; void* zDataTbl; void* nPhaseOneStep; void* iOalSz; void* iCookie; void* iWalCksum; void* nProgress; void* zIdx; void* zTbl; } ;
typedef  TYPE_2__ RbuState ;

/* Variables and functions */
 int RBU_STAGE_CKPT ; 
 int RBU_STAGE_MOVE ; 
 int RBU_STAGE_OAL ; 
#define  RBU_STATE_CKPT 137 
#define  RBU_STATE_COOKIE 136 
#define  RBU_STATE_DATATBL 135 
#define  RBU_STATE_IDX 134 
#define  RBU_STATE_OALSZ 133 
#define  RBU_STATE_PHASEONESTEP 132 
#define  RBU_STATE_PROGRESS 131 
#define  RBU_STATE_ROW 130 
#define  RBU_STATE_STAGE 129 
#define  RBU_STATE_TBL 128 
 void* SQLITE_CORRUPT ; 
 int SQLITE_OK ; 
 scalar_t__ SQLITE_ROW ; 
 int prepareFreeAndCollectError (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ rbuMalloc (TYPE_1__*,int) ; 
 void* rbuStrndup (char*,int*) ; 
 int sqlite3_column_int (int /*<<< orphan*/ *,int) ; 
 void* sqlite3_column_int64 (int /*<<< orphan*/ *,int) ; 
 scalar_t__ sqlite3_column_text (int /*<<< orphan*/ *,int) ; 
 int sqlite3_finalize (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sqlite3_mprintf (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3_step (int /*<<< orphan*/ *) ; 

__attribute__((used)) static RbuState *rbuLoadState(sqlite3rbu *p){
  RbuState *pRet = 0;
  sqlite3_stmt *pStmt = 0;
  int rc;
  int rc2;

  pRet = (RbuState*)rbuMalloc(p, sizeof(RbuState));
  if( pRet==0 ) return 0;

  rc = prepareFreeAndCollectError(p->dbRbu, &pStmt, &p->zErrmsg, 
      sqlite3_mprintf("SELECT k, v FROM %s.rbu_state", p->zStateDb)
  );
  while( rc==SQLITE_OK && SQLITE_ROW==sqlite3_step(pStmt) ){
    switch( sqlite3_column_int(pStmt, 0) ){
      case RBU_STATE_STAGE:
        pRet->eStage = sqlite3_column_int(pStmt, 1);
        if( pRet->eStage!=RBU_STAGE_OAL
         && pRet->eStage!=RBU_STAGE_MOVE
         && pRet->eStage!=RBU_STAGE_CKPT
        ){
          p->rc = SQLITE_CORRUPT;
        }
        break;

      case RBU_STATE_TBL:
        pRet->zTbl = rbuStrndup((char*)sqlite3_column_text(pStmt, 1), &rc);
        break;

      case RBU_STATE_IDX:
        pRet->zIdx = rbuStrndup((char*)sqlite3_column_text(pStmt, 1), &rc);
        break;

      case RBU_STATE_ROW:
        pRet->nRow = sqlite3_column_int(pStmt, 1);
        break;

      case RBU_STATE_PROGRESS:
        pRet->nProgress = sqlite3_column_int64(pStmt, 1);
        break;

      case RBU_STATE_CKPT:
        pRet->iWalCksum = sqlite3_column_int64(pStmt, 1);
        break;

      case RBU_STATE_COOKIE:
        pRet->iCookie = (u32)sqlite3_column_int64(pStmt, 1);
        break;

      case RBU_STATE_OALSZ:
        pRet->iOalSz = (u32)sqlite3_column_int64(pStmt, 1);
        break;

      case RBU_STATE_PHASEONESTEP:
        pRet->nPhaseOneStep = sqlite3_column_int64(pStmt, 1);
        break;

      case RBU_STATE_DATATBL:
        pRet->zDataTbl = rbuStrndup((char*)sqlite3_column_text(pStmt, 1), &rc);
        break;

      default:
        rc = SQLITE_CORRUPT;
        break;
    }
  }
  rc2 = sqlite3_finalize(pStmt);
  if( rc==SQLITE_OK ) rc = rc2;

  p->rc = rc;
  return pRet;
}