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
struct TYPE_13__ {int iRwclient; scalar_t__ pShmhdr; int /*<<< orphan*/  pEnv; int /*<<< orphan*/  pFS; TYPE_2__* pDatabase; scalar_t__ bReadonly; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_14__ {int /*<<< orphan*/  pFile; scalar_t__ bMultiProc; } ;
typedef  TYPE_2__ Database ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  LSM_LOCK_CHECKPOINTER ; 
 int /*<<< orphan*/  LSM_LOCK_DMS1 ; 
 int /*<<< orphan*/  LSM_LOCK_DMS2 ; 
 int /*<<< orphan*/  LSM_LOCK_DMS3 ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_RWCLIENT (int) ; 
 int /*<<< orphan*/  LSM_LOCK_UNLOCK ; 
 int LSM_OK ; 
 int /*<<< orphan*/  dbTruncateFile (TYPE_1__*) ; 
 int lsmCheckpointWrite (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lsmDetectRoTrans (TYPE_1__*,int*) ; 
 int /*<<< orphan*/  lsmEnvShmUnmap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lsmFlushTreeToDisk (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmFsCloseAndDeleteLog (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmFsUnmap (int /*<<< orphan*/ ) ; 
 int lsmShmLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int lsmShmTestLock (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lsmTreeHasOld (TYPE_1__*) ; 
 int lsmTreeLoadHeader (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ lsmTreeSize (TYPE_1__*) ; 

__attribute__((used)) static void doDbDisconnect(lsm_db *pDb){
  int rc;

  if( pDb->bReadonly ){
    lsmShmLock(pDb, LSM_LOCK_DMS3, LSM_LOCK_UNLOCK, 0);
  }else{
    /* Block for an exclusive lock on DMS1. This lock serializes all calls
    ** to doDbConnect() and doDbDisconnect() across all processes.  */
    rc = lsmShmLock(pDb, LSM_LOCK_DMS1, LSM_LOCK_EXCL, 1);
    if( rc==LSM_OK ){

      lsmShmLock(pDb, LSM_LOCK_DMS2, LSM_LOCK_UNLOCK, 0);

      /* Try an exclusive lock on DMS2. If successful, this is the last
      ** connection to the database. In this case flush the contents of the
      ** in-memory tree to disk and write a checkpoint.  */
      rc = lsmShmTestLock(pDb, LSM_LOCK_DMS2, 1, LSM_LOCK_EXCL);
      if( rc==LSM_OK ){
        rc = lsmShmTestLock(pDb, LSM_LOCK_CHECKPOINTER, 1, LSM_LOCK_EXCL);
      }
      if( rc==LSM_OK ){
        int bReadonly = 0;        /* True if there exist read-only conns. */

        /* Flush the in-memory tree, if required. If there is data to flush,
        ** this will create a new client snapshot in Database.pClient. The
        ** checkpoint (serialization) of this snapshot may be written to disk
        ** by the following block.  
        **
        ** There is no need to take a WRITER lock here. That there are no 
        ** other locks on DMS2 guarantees that there are no other read-write
        ** connections at this time (and the lock on DMS1 guarantees that
        ** no new ones may appear).
        */
        rc = lsmTreeLoadHeader(pDb, 0);
        if( rc==LSM_OK && (lsmTreeHasOld(pDb) || lsmTreeSize(pDb)>0) ){
          rc = lsmFlushTreeToDisk(pDb);
        }

        /* Now check if there are any read-only connections. If there are,
        ** then do not truncate the db file or unlink the shared-memory 
        ** region.  */
        if( rc==LSM_OK ){
          rc = lsmShmTestLock(pDb, LSM_LOCK_DMS3, 1, LSM_LOCK_EXCL);
          if( rc==LSM_BUSY ){
            bReadonly = 1;
            rc = LSM_OK;
          }
        }

        /* Write a checkpoint to disk. */
        if( rc==LSM_OK ){
          rc = lsmCheckpointWrite(pDb, 0);
        }

        /* If the checkpoint was written successfully, delete the log file
        ** and, if possible, truncate the database file.  */
        if( rc==LSM_OK ){
          int bRotrans = 0;
          Database *p = pDb->pDatabase;

          /* The log file may only be deleted if there are no clients 
          ** read-only clients running rotrans transactions.  */
          rc = lsmDetectRoTrans(pDb, &bRotrans);
          if( rc==LSM_OK && bRotrans==0 ){
            lsmFsCloseAndDeleteLog(pDb->pFS);
          }

          /* The database may only be truncated if there exist no read-only
          ** clients - either connected or running rotrans transactions. */
          if( bReadonly==0 && bRotrans==0 ){
            lsmFsUnmap(pDb->pFS);
            dbTruncateFile(pDb);
            if( p->pFile && p->bMultiProc ){
              lsmEnvShmUnmap(pDb->pEnv, p->pFile, 1);
            }
          }
        }
      }
    }

    if( pDb->iRwclient>=0 ){
      lsmShmLock(pDb, LSM_LOCK_RWCLIENT(pDb->iRwclient), LSM_LOCK_UNLOCK, 0);
      pDb->iRwclient = -1;
    }

    lsmShmLock(pDb, LSM_LOCK_DMS1, LSM_LOCK_UNLOCK, 0);
  }
  pDb->pShmhdr = 0;
}