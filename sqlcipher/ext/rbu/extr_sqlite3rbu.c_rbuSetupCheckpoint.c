#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_6__ ;
typedef  struct TYPE_17__   TYPE_5__ ;
typedef  struct TYPE_16__   TYPE_4__ ;
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
struct TYPE_16__ {scalar_t__ rc; scalar_t__ nFrame; int pgsz; scalar_t__ iWalCksum; int nPagePerSector; TYPE_2__* pTargetFd; scalar_t__ eStage; int /*<<< orphan*/  aBuf; int /*<<< orphan*/  nStep; int /*<<< orphan*/  dbMain; } ;
typedef  TYPE_4__ sqlite3rbu ;
struct TYPE_17__ {TYPE_3__* pMethods; } ;
typedef  TYPE_5__ sqlite3_file ;
struct TYPE_18__ {scalar_t__ iWalCksum; int /*<<< orphan*/  nRow; } ;
struct TYPE_15__ {int (* xSectorSize ) (TYPE_5__*) ;scalar_t__ (* xSync ) (TYPE_5__*,int /*<<< orphan*/ ) ;} ;
struct TYPE_14__ {TYPE_1__* pWalFd; TYPE_5__* pReal; } ;
struct TYPE_13__ {TYPE_5__* pReal; } ;
typedef  TYPE_6__ RbuState ;

/* Variables and functions */
 scalar_t__ RBU_STAGE_CAPTURE ; 
 scalar_t__ RBU_STAGE_CKPT ; 
 scalar_t__ RBU_STAGE_DONE ; 
 scalar_t__ SQLITE_DONE ; 
 int SQLITE_INTERNAL ; 
 scalar_t__ SQLITE_OK ; 
 int /*<<< orphan*/  SQLITE_SYNC_NORMAL ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  rbuMalloc (TYPE_4__*,int) ; 
 scalar_t__ rbuShmChecksum (TYPE_4__*) ; 
 void* sqlite3_exec (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_5__*) ; 
 scalar_t__ stub2 (TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void rbuSetupCheckpoint(sqlite3rbu *p, RbuState *pState){

  /* If pState is NULL, then the wal file may not have been opened and
  ** recovered. Running a read-statement here to ensure that doing so
  ** does not interfere with the "capture" process below.  */
  if( pState==0 ){
    p->eStage = 0;
    if( p->rc==SQLITE_OK ){
      p->rc = sqlite3_exec(p->dbMain, "SELECT * FROM sqlite_master", 0, 0, 0);
    }
  }

  /* Assuming no error has occurred, run a "restart" checkpoint with the
  ** sqlite3rbu.eStage variable set to CAPTURE. This turns on the following
  ** special behaviour in the rbu VFS:
  **
  **   * If the exclusive shm WRITER or READ0 lock cannot be obtained,
  **     the checkpoint fails with SQLITE_BUSY (normally SQLite would
  **     proceed with running a passive checkpoint instead of failing).
  **
  **   * Attempts to read from the *-wal file or write to the database file
  **     do not perform any IO. Instead, the frame/page combinations that
  **     would be read/written are recorded in the sqlite3rbu.aFrame[]
  **     array.
  **
  **   * Calls to xShmLock(UNLOCK) to release the exclusive shm WRITER, 
  **     READ0 and CHECKPOINT locks taken as part of the checkpoint are
  **     no-ops. These locks will not be released until the connection
  **     is closed.
  **
  **   * Attempting to xSync() the database file causes an SQLITE_INTERNAL 
  **     error.
  **
  ** As a result, unless an error (i.e. OOM or SQLITE_BUSY) occurs, the
  ** checkpoint below fails with SQLITE_INTERNAL, and leaves the aFrame[]
  ** array populated with a set of (frame -> page) mappings. Because the 
  ** WRITER, CHECKPOINT and READ0 locks are still held, it is safe to copy 
  ** data from the wal file into the database file according to the 
  ** contents of aFrame[].
  */
  if( p->rc==SQLITE_OK ){
    int rc2;
    p->eStage = RBU_STAGE_CAPTURE;
    rc2 = sqlite3_exec(p->dbMain, "PRAGMA main.wal_checkpoint=restart", 0, 0,0);
    if( rc2!=SQLITE_INTERNAL ) p->rc = rc2;
  }

  if( p->rc==SQLITE_OK && p->nFrame>0 ){
    p->eStage = RBU_STAGE_CKPT;
    p->nStep = (pState ? pState->nRow : 0);
    p->aBuf = rbuMalloc(p, p->pgsz);
    p->iWalCksum = rbuShmChecksum(p);
  }

  if( p->rc==SQLITE_OK ){
    if( p->nFrame==0 || (pState && pState->iWalCksum!=p->iWalCksum) ){
      p->rc = SQLITE_DONE;
      p->eStage = RBU_STAGE_DONE;
    }else{
      int nSectorSize;
      sqlite3_file *pDb = p->pTargetFd->pReal;
      sqlite3_file *pWal = p->pTargetFd->pWalFd->pReal;
      assert( p->nPagePerSector==0 );
      nSectorSize = pDb->pMethods->xSectorSize(pDb);
      if( nSectorSize>p->pgsz ){
        p->nPagePerSector = nSectorSize / p->pgsz;
      }else{
        p->nPagePerSector = 1;
      }

      /* Call xSync() on the wal file. This causes SQLite to sync the 
      ** directory in which the target database and the wal file reside, in 
      ** case it has not been synced since the rename() call in 
      ** rbuMoveOalFile(). */
      p->rc = pWal->pMethods->xSync(pWal, SQLITE_SYNC_NORMAL);
    }
  }
}