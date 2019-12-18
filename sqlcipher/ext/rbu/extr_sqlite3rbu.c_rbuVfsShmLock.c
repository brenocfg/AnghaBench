#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ eStage; int mLock; } ;
typedef  TYPE_2__ sqlite3rbu ;
typedef  int /*<<< orphan*/  sqlite3_file ;
struct TYPE_7__ {int openFlags; TYPE_4__* pReal; TYPE_2__* pRbu; } ;
typedef  TYPE_3__ rbu_file ;
struct TYPE_8__ {TYPE_1__* pMethods; } ;
struct TYPE_5__ {int (* xShmLock ) (TYPE_4__*,int,int,int) ;} ;

/* Variables and functions */
 scalar_t__ RBU_STAGE_CAPTURE ; 
 scalar_t__ RBU_STAGE_MOVE ; 
 scalar_t__ RBU_STAGE_OAL ; 
 int SQLITE_BUSY ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_DB ; 
 int SQLITE_OPEN_TEMP_DB ; 
 int SQLITE_SHM_EXCLUSIVE ; 
 int SQLITE_SHM_UNLOCK ; 
 int WAL_CKPT_LOCK ; 
 int WAL_LOCK_CKPT ; 
 int WAL_LOCK_READ0 ; 
 int WAL_LOCK_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int stub1 (TYPE_4__*,int,int,int) ; 

__attribute__((used)) static int rbuVfsShmLock(sqlite3_file *pFile, int ofst, int n, int flags){
  rbu_file *p = (rbu_file*)pFile;
  sqlite3rbu *pRbu = p->pRbu;
  int rc = SQLITE_OK;

#ifdef SQLITE_AMALGAMATION
    assert( WAL_CKPT_LOCK==1 );
#endif

  assert( p->openFlags & (SQLITE_OPEN_MAIN_DB|SQLITE_OPEN_TEMP_DB) );
  if( pRbu && (pRbu->eStage==RBU_STAGE_OAL || pRbu->eStage==RBU_STAGE_MOVE) ){
    /* Magic number 1 is the WAL_CKPT_LOCK lock. Preventing SQLite from
    ** taking this lock also prevents any checkpoints from occurring. 
    ** todo: really, it's not clear why this might occur, as 
    ** wal_autocheckpoint ought to be turned off.  */
    if( ofst==WAL_LOCK_CKPT && n==1 ) rc = SQLITE_BUSY;
  }else{
    int bCapture = 0;
    if( n==1 && (flags & SQLITE_SHM_EXCLUSIVE)
     && pRbu && pRbu->eStage==RBU_STAGE_CAPTURE
     && (ofst==WAL_LOCK_WRITE || ofst==WAL_LOCK_CKPT || ofst==WAL_LOCK_READ0)
    ){
      bCapture = 1;
    }

    if( bCapture==0 || 0==(flags & SQLITE_SHM_UNLOCK) ){
      rc = p->pReal->pMethods->xShmLock(p->pReal, ofst, n, flags);
      if( bCapture && rc==SQLITE_OK ){
        pRbu->mLock |= (1 << ofst);
      }
    }
  }

  return rc;
}