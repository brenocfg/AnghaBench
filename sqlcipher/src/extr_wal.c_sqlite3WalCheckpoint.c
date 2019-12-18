#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  sqlite3 ;
typedef  int /*<<< orphan*/  WalIndexHdr ;
struct TYPE_16__ {scalar_t__ mxFrame; } ;
struct TYPE_18__ {int ckptLock; int writeLock; TYPE_14__ hdr; TYPE_13__* pDbFd; scalar_t__ readOnly; } ;
typedef  TYPE_2__ Wal ;
struct TYPE_19__ {scalar_t__ nBackfill; } ;
struct TYPE_17__ {int iVersion; } ;
struct TYPE_15__ {TYPE_1__* pMethods; } ;

/* Variables and functions */
 int SQLITE_BUSY ; 
 int SQLITE_CHECKPOINT_PASSIVE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_READONLY ; 
 int /*<<< orphan*/  WALTRACE (char*) ; 
 int /*<<< orphan*/  WAL_CKPT_LOCK ; 
 int /*<<< orphan*/  WAL_WRITE_LOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memset (TYPE_14__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (TYPE_13__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3WalEndWriteTransaction (TYPE_2__*) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int walBusyLock (TYPE_2__*,int (*) (void*),void*,int /*<<< orphan*/ ,int) ; 
 int walCheckpoint (TYPE_2__*,int /*<<< orphan*/ *,int,int (*) (void*),void*,int,int /*<<< orphan*/ *) ; 
 TYPE_7__* walCkptInfo (TYPE_2__*) ; 
 int walIndexReadHdr (TYPE_2__*,int*) ; 
 int walLockExclusive (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int walPagesize (TYPE_2__*) ; 
 int /*<<< orphan*/  walUnlockExclusive (TYPE_2__*,int /*<<< orphan*/ ,int) ; 

int sqlite3WalCheckpoint(
  Wal *pWal,                      /* Wal connection */
  sqlite3 *db,                    /* Check this handle's interrupt flag */
  int eMode,                      /* PASSIVE, FULL, RESTART, or TRUNCATE */
  int (*xBusy)(void*),            /* Function to call when busy */
  void *pBusyArg,                 /* Context argument for xBusyHandler */
  int sync_flags,                 /* Flags to sync db file with (or 0) */
  int nBuf,                       /* Size of temporary buffer */
  u8 *zBuf,                       /* Temporary buffer to use */
  int *pnLog,                     /* OUT: Number of frames in WAL */
  int *pnCkpt                     /* OUT: Number of backfilled frames in WAL */
){
  int rc;                         /* Return code */
  int isChanged = 0;              /* True if a new wal-index header is loaded */
  int eMode2 = eMode;             /* Mode to pass to walCheckpoint() */
  int (*xBusy2)(void*) = xBusy;   /* Busy handler for eMode2 */

  assert( pWal->ckptLock==0 );
  assert( pWal->writeLock==0 );

  /* EVIDENCE-OF: R-62920-47450 The busy-handler callback is never invoked
  ** in the SQLITE_CHECKPOINT_PASSIVE mode. */
  assert( eMode!=SQLITE_CHECKPOINT_PASSIVE || xBusy==0 );

  if( pWal->readOnly ) return SQLITE_READONLY;
  WALTRACE(("WAL%p: checkpoint begins\n", pWal));

  /* IMPLEMENTATION-OF: R-62028-47212 All calls obtain an exclusive 
  ** "checkpoint" lock on the database file. */
  rc = walLockExclusive(pWal, WAL_CKPT_LOCK, 1);
  if( rc ){
    /* EVIDENCE-OF: R-10421-19736 If any other process is running a
    ** checkpoint operation at the same time, the lock cannot be obtained and
    ** SQLITE_BUSY is returned.
    ** EVIDENCE-OF: R-53820-33897 Even if there is a busy-handler configured,
    ** it will not be invoked in this case.
    */
    testcase( rc==SQLITE_BUSY );
    testcase( xBusy!=0 );
    return rc;
  }
  pWal->ckptLock = 1;

  /* IMPLEMENTATION-OF: R-59782-36818 The SQLITE_CHECKPOINT_FULL, RESTART and
  ** TRUNCATE modes also obtain the exclusive "writer" lock on the database
  ** file.
  **
  ** EVIDENCE-OF: R-60642-04082 If the writer lock cannot be obtained
  ** immediately, and a busy-handler is configured, it is invoked and the
  ** writer lock retried until either the busy-handler returns 0 or the
  ** lock is successfully obtained.
  */
  if( eMode!=SQLITE_CHECKPOINT_PASSIVE ){
    rc = walBusyLock(pWal, xBusy, pBusyArg, WAL_WRITE_LOCK, 1);
    if( rc==SQLITE_OK ){
      pWal->writeLock = 1;
    }else if( rc==SQLITE_BUSY ){
      eMode2 = SQLITE_CHECKPOINT_PASSIVE;
      xBusy2 = 0;
      rc = SQLITE_OK;
    }
  }

  /* Read the wal-index header. */
  if( rc==SQLITE_OK ){
    rc = walIndexReadHdr(pWal, &isChanged);
    if( isChanged && pWal->pDbFd->pMethods->iVersion>=3 ){
      sqlite3OsUnfetch(pWal->pDbFd, 0, 0);
    }
  }

  /* Copy data from the log to the database file. */
  if( rc==SQLITE_OK ){

    if( pWal->hdr.mxFrame && walPagesize(pWal)!=nBuf ){
      rc = SQLITE_CORRUPT_BKPT;
    }else{
      rc = walCheckpoint(pWal, db, eMode2, xBusy2, pBusyArg, sync_flags, zBuf);
    }

    /* If no error occurred, set the output variables. */
    if( rc==SQLITE_OK || rc==SQLITE_BUSY ){
      if( pnLog ) *pnLog = (int)pWal->hdr.mxFrame;
      if( pnCkpt ) *pnCkpt = (int)(walCkptInfo(pWal)->nBackfill);
    }
  }

  if( isChanged ){
    /* If a new wal-index header was loaded before the checkpoint was 
    ** performed, then the pager-cache associated with pWal is now
    ** out of date. So zero the cached wal-index header to ensure that
    ** next time the pager opens a snapshot on this database it knows that
    ** the cache needs to be reset.
    */
    memset(&pWal->hdr, 0, sizeof(WalIndexHdr));
  }

  /* Release the locks. */
  sqlite3WalEndWriteTransaction(pWal);
  walUnlockExclusive(pWal, WAL_CKPT_LOCK, 1);
  pWal->ckptLock = 0;
  WALTRACE(("WAL%p: checkpoint %s\n", pWal, rc ? "failed" : "ok"));
  return (rc==SQLITE_OK && eMode!=eMode2 ? SQLITE_BUSY : rc);
}