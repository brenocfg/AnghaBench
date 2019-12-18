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
struct TYPE_7__ {scalar_t__ nRef; scalar_t__ hShm; int exclMask; int sharedMask; int /*<<< orphan*/  pShmMutex; } ;
typedef  TYPE_2__ unixShmNode ;
struct TYPE_8__ {TYPE_1__* pInode; } ;
typedef  TYPE_3__ unixFile ;
typedef  int u16 ;
struct flock {int l_type; int l_start; int l_len; int /*<<< orphan*/  l_whence; } ;
struct TYPE_6__ {TYPE_2__* pShmNode; } ;

/* Variables and functions */
 int F_RDLCK ; 
 int F_UNLCK ; 
 int F_WRLCK ; 
 int /*<<< orphan*/  OSTRACE (char*) ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int SQLITE_BUSY ; 
 int SQLITE_OK ; 
 int SQLITE_SHM_NLOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 int osSetPosixAdvisoryLock (scalar_t__,struct flock*,TYPE_3__*) ; 
 scalar_t__ sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 scalar_t__ unixMutexHeld () ; 

__attribute__((used)) static int unixShmSystemLock(
  unixFile *pFile,       /* Open connection to the WAL file */
  int lockType,          /* F_UNLCK, F_RDLCK, or F_WRLCK */
  int ofst,              /* First byte of the locking range */
  int n                  /* Number of bytes to lock */
){
  unixShmNode *pShmNode; /* Apply locks to this open shared-memory segment */
  struct flock f;        /* The posix advisory locking structure */
  int rc = SQLITE_OK;    /* Result code form fcntl() */

  /* Access to the unixShmNode object is serialized by the caller */
  pShmNode = pFile->pInode->pShmNode;
  assert( pShmNode->nRef==0 || sqlite3_mutex_held(pShmNode->pShmMutex) );
  assert( pShmNode->nRef>0 || unixMutexHeld() );

  /* Shared locks never span more than one byte */
  assert( n==1 || lockType!=F_RDLCK );

  /* Locks are within range */
  assert( n>=1 && n<=SQLITE_SHM_NLOCK );

  if( pShmNode->hShm>=0 ){
    /* Initialize the locking parameters */
    f.l_type = lockType;
    f.l_whence = SEEK_SET;
    f.l_start = ofst;
    f.l_len = n;
    rc = osSetPosixAdvisoryLock(pShmNode->hShm, &f, pFile);
    rc = (rc!=(-1)) ? SQLITE_OK : SQLITE_BUSY;
  }

  /* Update the global lock state and do debug tracing */
#ifdef SQLITE_DEBUG
  { u16 mask;
  OSTRACE(("SHM-LOCK "));
  mask = ofst>31 ? 0xffff : (1<<(ofst+n)) - (1<<ofst);
  if( rc==SQLITE_OK ){
    if( lockType==F_UNLCK ){
      OSTRACE(("unlock %d ok", ofst));
      pShmNode->exclMask &= ~mask;
      pShmNode->sharedMask &= ~mask;
    }else if( lockType==F_RDLCK ){
      OSTRACE(("read-lock %d ok", ofst));
      pShmNode->exclMask &= ~mask;
      pShmNode->sharedMask |= mask;
    }else{
      assert( lockType==F_WRLCK );
      OSTRACE(("write-lock %d ok", ofst));
      pShmNode->exclMask |= mask;
      pShmNode->sharedMask &= ~mask;
    }
  }else{
    if( lockType==F_UNLCK ){
      OSTRACE(("unlock %d failed", ofst));
    }else if( lockType==F_RDLCK ){
      OSTRACE(("read-lock failed"));
    }else{
      assert( lockType==F_WRLCK );
      OSTRACE(("write-lock %d failed", ofst));
    }
  }
  OSTRACE((" - afterwards %03x,%03x\n",
           pShmNode->sharedMask, pShmNode->exclMask));
  }
#endif

  return rc;        
}