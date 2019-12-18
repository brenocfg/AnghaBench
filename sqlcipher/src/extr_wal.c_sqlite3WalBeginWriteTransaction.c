#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  WalIndexHdr ;
struct TYPE_6__ {scalar_t__ readLock; int writeLock; scalar_t__ iReCksum; int /*<<< orphan*/  hdr; scalar_t__ readOnly; } ;
typedef  TYPE_1__ Wal ;

/* Variables and functions */
 int SQLITE_BUSY_SNAPSHOT ; 
 int SQLITE_READONLY ; 
 int /*<<< orphan*/  WAL_WRITE_LOCK ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,void*,int) ; 
 scalar_t__ walIndexHdr (TYPE_1__*) ; 
 int walLockExclusive (TYPE_1__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  walUnlockExclusive (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

int sqlite3WalBeginWriteTransaction(Wal *pWal){
  int rc;

  /* Cannot start a write transaction without first holding a read
  ** transaction. */
  assert( pWal->readLock>=0 );
  assert( pWal->writeLock==0 && pWal->iReCksum==0 );

  if( pWal->readOnly ){
    return SQLITE_READONLY;
  }

  /* Only one writer allowed at a time.  Get the write lock.  Return
  ** SQLITE_BUSY if unable.
  */
  rc = walLockExclusive(pWal, WAL_WRITE_LOCK, 1);
  if( rc ){
    return rc;
  }
  pWal->writeLock = 1;

  /* If another connection has written to the database file since the
  ** time the read transaction on this connection was started, then
  ** the write is disallowed.
  */
  if( memcmp(&pWal->hdr, (void *)walIndexHdr(pWal), sizeof(WalIndexHdr))!=0 ){
    walUnlockExclusive(pWal, WAL_WRITE_LOCK, 1);
    pWal->writeLock = 0;
    rc = SQLITE_BUSY_SNAPSHOT;
  }

  return rc;
}