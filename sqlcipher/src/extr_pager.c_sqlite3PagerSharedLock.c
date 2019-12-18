#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  sqlite3_vfs ;
typedef  int /*<<< orphan*/  dbFileVers ;
struct TYPE_18__ {scalar_t__ eState; int errCode; scalar_t__ tempFile; scalar_t__ eLock; int hasHeldSharedLock; scalar_t__ pWal; int /*<<< orphan*/  dbSize; int /*<<< orphan*/  fd; int /*<<< orphan*/  dbFileVers; scalar_t__ exclusiveMode; int /*<<< orphan*/  jfd; int /*<<< orphan*/  zJournal; int /*<<< orphan*/ * pVfs; scalar_t__ readOnly; int /*<<< orphan*/  pPCache; } ;
typedef  TYPE_1__ Pager ;

/* Variables and functions */
 scalar_t__ EXCLUSIVE_LOCK ; 
 int /*<<< orphan*/  IOTRACE (char*) ; 
 int /*<<< orphan*/  MEMDB ; 
 scalar_t__ NO_LOCK ; 
 scalar_t__ PAGER_OPEN ; 
 scalar_t__ PAGER_READER ; 
 scalar_t__ SHARED_LOCK ; 
 int /*<<< orphan*/  SQLITE_ACCESS_EXISTS ; 
 int SQLITE_CANTOPEN_BKPT ; 
 int SQLITE_IOERR_SHORT_READ ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_MAIN_JOURNAL ; 
 int SQLITE_OPEN_READONLY ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_READONLY_ROLLBACK ; 
 scalar_t__ UNKNOWN_LOCK ; 
 scalar_t__ USEFETCH (TYPE_1__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int assert_pager_state (TYPE_1__*) ; 
 int hasHotJournal (TYPE_1__*,int*) ; 
 scalar_t__ isOpen (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int pagerBeginReadTransaction (TYPE_1__*) ; 
 int pagerLockDb (TYPE_1__*,scalar_t__) ; 
 int pagerOpenWalIfPresent (TYPE_1__*) ; 
 int pagerPagecount (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int pagerSyncHotJournal (TYPE_1__*) ; 
 int /*<<< orphan*/  pagerUnlockDb (TYPE_1__*,scalar_t__) ; 
 scalar_t__ pagerUseWal (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_error (TYPE_1__*,int) ; 
 int pager_playback (TYPE_1__*,int) ; 
 int /*<<< orphan*/  pager_reset (TYPE_1__*) ; 
 int /*<<< orphan*/  pager_unlock (TYPE_1__*) ; 
 int pager_wait_on_lock (TYPE_1__*,scalar_t__) ; 
 int sqlite3OsAccess (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ ) ; 
 int sqlite3OsOpen (int /*<<< orphan*/ * const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*) ; 
 int sqlite3OsRead (int /*<<< orphan*/ ,char**,int,int) ; 
 int /*<<< orphan*/  sqlite3OsUnfetch (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3PcacheRefCount (int /*<<< orphan*/ ) ; 

int sqlite3PagerSharedLock(Pager *pPager){
  int rc = SQLITE_OK;                /* Return code */

  /* This routine is only called from b-tree and only when there are no
  ** outstanding pages. This implies that the pager state should either
  ** be OPEN or READER. READER is only possible if the pager is or was in 
  ** exclusive access mode.  */
  assert( sqlite3PcacheRefCount(pPager->pPCache)==0 );
  assert( assert_pager_state(pPager) );
  assert( pPager->eState==PAGER_OPEN || pPager->eState==PAGER_READER );
  assert( pPager->errCode==SQLITE_OK );

  if( !pagerUseWal(pPager) && pPager->eState==PAGER_OPEN ){
    int bHotJournal = 1;          /* True if there exists a hot journal-file */

    assert( !MEMDB );
    assert( pPager->tempFile==0 || pPager->eLock==EXCLUSIVE_LOCK );

    rc = pager_wait_on_lock(pPager, SHARED_LOCK);
    if( rc!=SQLITE_OK ){
      assert( pPager->eLock==NO_LOCK || pPager->eLock==UNKNOWN_LOCK );
      goto failed;
    }

    /* If a journal file exists, and there is no RESERVED lock on the
    ** database file, then it either needs to be played back or deleted.
    */
    if( pPager->eLock<=SHARED_LOCK ){
      rc = hasHotJournal(pPager, &bHotJournal);
    }
    if( rc!=SQLITE_OK ){
      goto failed;
    }
    if( bHotJournal ){
      if( pPager->readOnly ){
        rc = SQLITE_READONLY_ROLLBACK;
        goto failed;
      }

      /* Get an EXCLUSIVE lock on the database file. At this point it is
      ** important that a RESERVED lock is not obtained on the way to the
      ** EXCLUSIVE lock. If it were, another process might open the
      ** database file, detect the RESERVED lock, and conclude that the
      ** database is safe to read while this process is still rolling the 
      ** hot-journal back.
      ** 
      ** Because the intermediate RESERVED lock is not requested, any
      ** other process attempting to access the database file will get to 
      ** this point in the code and fail to obtain its own EXCLUSIVE lock 
      ** on the database file.
      **
      ** Unless the pager is in locking_mode=exclusive mode, the lock is
      ** downgraded to SHARED_LOCK before this function returns.
      */
      rc = pagerLockDb(pPager, EXCLUSIVE_LOCK);
      if( rc!=SQLITE_OK ){
        goto failed;
      }
 
      /* If it is not already open and the file exists on disk, open the 
      ** journal for read/write access. Write access is required because 
      ** in exclusive-access mode the file descriptor will be kept open 
      ** and possibly used for a transaction later on. Also, write-access 
      ** is usually required to finalize the journal in journal_mode=persist 
      ** mode (and also for journal_mode=truncate on some systems).
      **
      ** If the journal does not exist, it usually means that some 
      ** other connection managed to get in and roll it back before 
      ** this connection obtained the exclusive lock above. Or, it 
      ** may mean that the pager was in the error-state when this
      ** function was called and the journal file does not exist.
      */
      if( !isOpen(pPager->jfd) ){
        sqlite3_vfs * const pVfs = pPager->pVfs;
        int bExists;              /* True if journal file exists */
        rc = sqlite3OsAccess(
            pVfs, pPager->zJournal, SQLITE_ACCESS_EXISTS, &bExists);
        if( rc==SQLITE_OK && bExists ){
          int fout = 0;
          int f = SQLITE_OPEN_READWRITE|SQLITE_OPEN_MAIN_JOURNAL;
          assert( !pPager->tempFile );
          rc = sqlite3OsOpen(pVfs, pPager->zJournal, pPager->jfd, f, &fout);
          assert( rc!=SQLITE_OK || isOpen(pPager->jfd) );
          if( rc==SQLITE_OK && fout&SQLITE_OPEN_READONLY ){
            rc = SQLITE_CANTOPEN_BKPT;
            sqlite3OsClose(pPager->jfd);
          }
        }
      }
 
      /* Playback and delete the journal.  Drop the database write
      ** lock and reacquire the read lock. Purge the cache before
      ** playing back the hot-journal so that we don't end up with
      ** an inconsistent cache.  Sync the hot journal before playing
      ** it back since the process that crashed and left the hot journal
      ** probably did not sync it and we are required to always sync
      ** the journal before playing it back.
      */
      if( isOpen(pPager->jfd) ){
        assert( rc==SQLITE_OK );
        rc = pagerSyncHotJournal(pPager);
        if( rc==SQLITE_OK ){
          rc = pager_playback(pPager, !pPager->tempFile);
          pPager->eState = PAGER_OPEN;
        }
      }else if( !pPager->exclusiveMode ){
        pagerUnlockDb(pPager, SHARED_LOCK);
      }

      if( rc!=SQLITE_OK ){
        /* This branch is taken if an error occurs while trying to open
        ** or roll back a hot-journal while holding an EXCLUSIVE lock. The
        ** pager_unlock() routine will be called before returning to unlock
        ** the file. If the unlock attempt fails, then Pager.eLock must be
        ** set to UNKNOWN_LOCK (see the comment above the #define for 
        ** UNKNOWN_LOCK above for an explanation). 
        **
        ** In order to get pager_unlock() to do this, set Pager.eState to
        ** PAGER_ERROR now. This is not actually counted as a transition
        ** to ERROR state in the state diagram at the top of this file,
        ** since we know that the same call to pager_unlock() will very
        ** shortly transition the pager object to the OPEN state. Calling
        ** assert_pager_state() would fail now, as it should not be possible
        ** to be in ERROR state when there are zero outstanding page 
        ** references.
        */
        pager_error(pPager, rc);
        goto failed;
      }

      assert( pPager->eState==PAGER_OPEN );
      assert( (pPager->eLock==SHARED_LOCK)
           || (pPager->exclusiveMode && pPager->eLock>SHARED_LOCK)
      );
    }

    if( !pPager->tempFile && pPager->hasHeldSharedLock ){
      /* The shared-lock has just been acquired then check to
      ** see if the database has been modified.  If the database has changed,
      ** flush the cache.  The hasHeldSharedLock flag prevents this from
      ** occurring on the very first access to a file, in order to save a
      ** single unnecessary sqlite3OsRead() call at the start-up.
      **
      ** Database changes are detected by looking at 15 bytes beginning
      ** at offset 24 into the file.  The first 4 of these 16 bytes are
      ** a 32-bit counter that is incremented with each change.  The
      ** other bytes change randomly with each file change when
      ** a codec is in use.
      ** 
      ** There is a vanishingly small chance that a change will not be 
      ** detected.  The chance of an undetected change is so small that
      ** it can be neglected.
      */
      char dbFileVers[sizeof(pPager->dbFileVers)];

      IOTRACE(("CKVERS %p %d\n", pPager, sizeof(dbFileVers)));
      rc = sqlite3OsRead(pPager->fd, &dbFileVers, sizeof(dbFileVers), 24);
      if( rc!=SQLITE_OK ){
        if( rc!=SQLITE_IOERR_SHORT_READ ){
          goto failed;
        }
        memset(dbFileVers, 0, sizeof(dbFileVers));
      }

      if( memcmp(pPager->dbFileVers, dbFileVers, sizeof(dbFileVers))!=0 ){
        pager_reset(pPager);

        /* Unmap the database file. It is possible that external processes
        ** may have truncated the database file and then extended it back
        ** to its original size while this process was not holding a lock.
        ** In this case there may exist a Pager.pMap mapping that appears
        ** to be the right size but is not actually valid. Avoid this
        ** possibility by unmapping the db here. */
        if( USEFETCH(pPager) ){
          sqlite3OsUnfetch(pPager->fd, 0, 0);
        }
      }
    }

    /* If there is a WAL file in the file-system, open this database in WAL
    ** mode. Otherwise, the following function call is a no-op.
    */
    rc = pagerOpenWalIfPresent(pPager);
#ifndef SQLITE_OMIT_WAL
    assert( pPager->pWal==0 || rc==SQLITE_OK );
#endif
  }

  if( pagerUseWal(pPager) ){
    assert( rc==SQLITE_OK );
    rc = pagerBeginReadTransaction(pPager);
  }

  if( pPager->tempFile==0 && pPager->eState==PAGER_OPEN && rc==SQLITE_OK ){
    rc = pagerPagecount(pPager, &pPager->dbSize);
  }

 failed:
  if( rc!=SQLITE_OK ){
    assert( !MEMDB );
    pager_unlock(pPager);
    assert( pPager->eState==PAGER_OPEN );
  }else{
    pPager->eState = PAGER_READER;
    pPager->hasHeldSharedLock = 1;
  }
  return rc;
}