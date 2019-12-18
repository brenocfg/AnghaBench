#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ szOsFile; } ;
typedef  TYPE_1__ sqlite3_vfs ;
typedef  int /*<<< orphan*/  sqlite3_file ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_9__ {int readLock; char const* zWalName; int syncHeader; int padToSectorBoundary; int /*<<< orphan*/ * pWalFd; int /*<<< orphan*/  readOnly; int /*<<< orphan*/  exclusiveMode; int /*<<< orphan*/  mxWalSize; int /*<<< orphan*/ * pDbFd; TYPE_1__* pVfs; } ;
typedef  TYPE_2__ Wal ;

/* Variables and functions */
 int SQLITE_IOCAP_POWERSAFE_OVERWRITE ; 
 int SQLITE_IOCAP_SEQUENTIAL ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 int SQLITE_OPEN_CREATE ; 
 int SQLITE_OPEN_READONLY ; 
 int SQLITE_OPEN_READWRITE ; 
 int SQLITE_OPEN_WAL ; 
 int UNIX_SHM_BASE ; 
 int WALINDEX_HDR_SIZE ; 
 int WALINDEX_LOCK_OFFSET ; 
 int /*<<< orphan*/  WALTRACE (char*) ; 
 int /*<<< orphan*/  WAL_HEAPMEMORY_MODE ; 
 int /*<<< orphan*/  WAL_NORMAL_MODE ; 
 int /*<<< orphan*/  WAL_RDONLY ; 
 int WIN_SHM_BASE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ sqlite3MallocZero (scalar_t__) ; 
 int /*<<< orphan*/  sqlite3OsClose (int /*<<< orphan*/ *) ; 
 int sqlite3OsDeviceCharacteristics (int /*<<< orphan*/ *) ; 
 int sqlite3OsOpen (TYPE_1__*,char const*,int /*<<< orphan*/ *,int,int*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_2__*) ; 
 int /*<<< orphan*/  walIndexClose (TYPE_2__*,int /*<<< orphan*/ ) ; 

int sqlite3WalOpen(
  sqlite3_vfs *pVfs,              /* vfs module to open wal and wal-index */
  sqlite3_file *pDbFd,            /* The open database file */
  const char *zWalName,           /* Name of the WAL file */
  int bNoShm,                     /* True to run in heap-memory mode */
  i64 mxWalSize,                  /* Truncate WAL to this size on reset */
  Wal **ppWal                     /* OUT: Allocated Wal handle */
){
  int rc;                         /* Return Code */
  Wal *pRet;                      /* Object to allocate and return */
  int flags;                      /* Flags passed to OsOpen() */

  assert( zWalName && zWalName[0] );
  assert( pDbFd );

  /* In the amalgamation, the os_unix.c and os_win.c source files come before
  ** this source file.  Verify that the #defines of the locking byte offsets
  ** in os_unix.c and os_win.c agree with the WALINDEX_LOCK_OFFSET value.
  ** For that matter, if the lock offset ever changes from its initial design
  ** value of 120, we need to know that so there is an assert() to check it.
  */
  assert( 120==WALINDEX_LOCK_OFFSET );
  assert( 136==WALINDEX_HDR_SIZE );
#ifdef WIN_SHM_BASE
  assert( WIN_SHM_BASE==WALINDEX_LOCK_OFFSET );
#endif
#ifdef UNIX_SHM_BASE
  assert( UNIX_SHM_BASE==WALINDEX_LOCK_OFFSET );
#endif


  /* Allocate an instance of struct Wal to return. */
  *ppWal = 0;
  pRet = (Wal*)sqlite3MallocZero(sizeof(Wal) + pVfs->szOsFile);
  if( !pRet ){
    return SQLITE_NOMEM_BKPT;
  }

  pRet->pVfs = pVfs;
  pRet->pWalFd = (sqlite3_file *)&pRet[1];
  pRet->pDbFd = pDbFd;
  pRet->readLock = -1;
  pRet->mxWalSize = mxWalSize;
  pRet->zWalName = zWalName;
  pRet->syncHeader = 1;
  pRet->padToSectorBoundary = 1;
  pRet->exclusiveMode = (bNoShm ? WAL_HEAPMEMORY_MODE: WAL_NORMAL_MODE);

  /* Open file handle on the write-ahead log file. */
  flags = (SQLITE_OPEN_READWRITE|SQLITE_OPEN_CREATE|SQLITE_OPEN_WAL);
  rc = sqlite3OsOpen(pVfs, zWalName, pRet->pWalFd, flags, &flags);
  if( rc==SQLITE_OK && flags&SQLITE_OPEN_READONLY ){
    pRet->readOnly = WAL_RDONLY;
  }

  if( rc!=SQLITE_OK ){
    walIndexClose(pRet, 0);
    sqlite3OsClose(pRet->pWalFd);
    sqlite3_free(pRet);
  }else{
    int iDC = sqlite3OsDeviceCharacteristics(pDbFd);
    if( iDC & SQLITE_IOCAP_SEQUENTIAL ){ pRet->syncHeader = 0; }
    if( iDC & SQLITE_IOCAP_POWERSAFE_OVERWRITE ){
      pRet->padToSectorBoundary = 0;
    }
    *ppWal = pRet;
    WALTRACE(("WAL%d: opened\n", pRet));
  }
  return rc;
}