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
 int EACCES ; 
 int EAGAIN ; 
#define  F_RDLCK 130 
 int /*<<< orphan*/  F_SETLK ; 
#define  F_UNLCK 129 
#define  F_WRLCK 128 
 int LSM_BUSY ; 
 int LSM_IOERR_BKPT ; 
 size_t LSM_LOCK_EXCL ; 
 size_t LSM_LOCK_SHARED ; 
 size_t LSM_LOCK_UNLOCK ; 
 int LSM_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int array_size (short const*) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 scalar_t__ fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct flock*) ; 
 int /*<<< orphan*/  memset (struct flock*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lsmPosixOsLock(lsm_file *pFile, int iLock, int eType){
  int rc = LSM_OK;
  PosixFile *p = (PosixFile *)pFile;
  static const short aType[3] = { F_UNLCK, F_RDLCK, F_WRLCK };
  struct flock lock;

  assert( aType[LSM_LOCK_UNLOCK]==F_UNLCK );
  assert( aType[LSM_LOCK_SHARED]==F_RDLCK );
  assert( aType[LSM_LOCK_EXCL]==F_WRLCK );
  assert( eType>=0 && eType<array_size(aType) );
  assert( iLock>0 && iLock<=32 );

  memset(&lock, 0, sizeof(lock));
  lock.l_whence = SEEK_SET;
  lock.l_len = 1;
  lock.l_type = aType[eType];
  lock.l_start = (4096-iLock);

  if( fcntl(p->fd, F_SETLK, &lock) ){
    int e = errno;
    if( e==EACCES || e==EAGAIN ){
      rc = LSM_BUSY;
    }else{
      rc = LSM_IOERR_BKPT;
    }
  }

  return rc;
}