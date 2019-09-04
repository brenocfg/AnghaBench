#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int isUnlocked; int /*<<< orphan*/  zFilename; int /*<<< orphan*/  hShm; scalar_t__ isReadonly; } ;
typedef  TYPE_1__ unixShmNode ;
typedef  int /*<<< orphan*/  unixFile ;
struct flock {int l_len; scalar_t__ l_type; int /*<<< orphan*/  l_start; int /*<<< orphan*/  l_whence; } ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETLK ; 
 scalar_t__ F_RDLCK ; 
 scalar_t__ F_UNLCK ; 
 scalar_t__ F_WRLCK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SQLITE_BUSY ; 
 int SQLITE_IOERR_LOCK ; 
 int /*<<< orphan*/  SQLITE_IOERR_SHMOPEN ; 
 int SQLITE_OK ; 
 int SQLITE_READONLY_CANTINIT ; 
 int /*<<< orphan*/  UNIX_SHM_DMS ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ osFcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 scalar_t__ robust_ftruncate (int /*<<< orphan*/ ,int) ; 
 int unixLogError (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int unixShmSystemLock (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int unixLockSharedMemory(unixFile *pDbFd, unixShmNode *pShmNode){
  struct flock lock;
  int rc = SQLITE_OK;

  /* Use F_GETLK to determine the locks other processes are holding
  ** on the DMS byte. If it indicates that another process is holding
  ** a SHARED lock, then this process may also take a SHARED lock
  ** and proceed with opening the *-shm file. 
  **
  ** Or, if no other process is holding any lock, then this process
  ** is the first to open it. In this case take an EXCLUSIVE lock on the
  ** DMS byte and truncate the *-shm file to zero bytes in size. Then
  ** downgrade to a SHARED lock on the DMS byte.
  **
  ** If another process is holding an EXCLUSIVE lock on the DMS byte,
  ** return SQLITE_BUSY to the caller (it will try again). An earlier
  ** version of this code attempted the SHARED lock at this point. But
  ** this introduced a subtle race condition: if the process holding
  ** EXCLUSIVE failed just before truncating the *-shm file, then this
  ** process might open and use the *-shm file without truncating it.
  ** And if the *-shm file has been corrupted by a power failure or
  ** system crash, the database itself may also become corrupt.  */
  lock.l_whence = SEEK_SET;
  lock.l_start = UNIX_SHM_DMS;
  lock.l_len = 1;
  lock.l_type = F_WRLCK;
  if( osFcntl(pShmNode->hShm, F_GETLK, &lock)!=0 ) {
    rc = SQLITE_IOERR_LOCK;
  }else if( lock.l_type==F_UNLCK ){
    if( pShmNode->isReadonly ){
      pShmNode->isUnlocked = 1;
      rc = SQLITE_READONLY_CANTINIT;
    }else{
      rc = unixShmSystemLock(pDbFd, F_WRLCK, UNIX_SHM_DMS, 1);
      /* The first connection to attach must truncate the -shm file.  We
      ** truncate to 3 bytes (an arbitrary small number, less than the
      ** -shm header size) rather than 0 as a system debugging aid, to
      ** help detect if a -shm file truncation is legitimate or is the work
      ** or a rogue process. */
      if( rc==SQLITE_OK && robust_ftruncate(pShmNode->hShm, 3) ){
        rc = unixLogError(SQLITE_IOERR_SHMOPEN,"ftruncate",pShmNode->zFilename);
      }
    }
  }else if( lock.l_type==F_WRLCK ){
    rc = SQLITE_BUSY;
  }

  if( rc==SQLITE_OK ){
    assert( lock.l_type==F_UNLCK || lock.l_type==F_RDLCK );
    rc = unixShmSystemLock(pDbFd, F_RDLCK, UNIX_SHM_DMS, 1);
  }
  return rc;
}