#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct flock {int l_len; short l_type; int l_start; int /*<<< orphan*/  l_whence; } ;
typedef  int /*<<< orphan*/  lsm_file ;
typedef  int /*<<< orphan*/  lock ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int /*<<< orphan*/  F_GETLK ; 
#define  F_RDLCK 129 
 short F_UNLCK ; 
#define  F_WRLCK 128 
 int LSM_BUSY ; 
 int LSM_IOERR_BKPT ; 
 int LSM_LOCK_EXCL ; 
 int LSM_LOCK_SHARED ; 
 int LSM_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int array_size (short const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  memset (struct flock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lsmPosixOsTestLock(lsm_file *pFile, int iLock, int nLock, int eType){
  int rc = LSM_OK;
  PosixFile *p = (PosixFile *)pFile;
  static const short aType[3] = { 0, F_RDLCK, F_WRLCK };
  struct flock lock;

  assert( eType==LSM_LOCK_SHARED || eType==LSM_LOCK_EXCL );
  assert( aType[LSM_LOCK_SHARED]==F_RDLCK );
  assert( aType[LSM_LOCK_EXCL]==F_WRLCK );
  assert( eType>=0 && eType<array_size(aType) );
  assert( iLock>0 && iLock<=32 );

  memset(&lock, 0, sizeof(lock));
  lock.l_whence = SEEK_SET;
  lock.l_len = nLock;
  lock.l_type = aType[eType];
  lock.l_start = (4096-iLock-nLock+1);

  if( fcntl(p->fd, F_GETLK, &lock) ){
    rc = LSM_IOERR_BKPT;
  }else if( lock.l_type!=F_UNLCK ){
    rc = LSM_BUSY;
  }

  return rc;
}