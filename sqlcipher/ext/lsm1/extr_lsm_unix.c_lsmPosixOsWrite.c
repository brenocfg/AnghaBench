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
typedef  scalar_t__ ssize_t ;
typedef  scalar_t__ off_t ;
typedef  scalar_t__ lsm_i64 ;
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int LSM_IOERR_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  SEEK_SET ; 
 scalar_t__ lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int /*<<< orphan*/ ,void*,size_t) ; 

__attribute__((used)) static int lsmPosixOsWrite(
  lsm_file *pFile,                /* File to write to */
  lsm_i64 iOff,                   /* Offset to write to */
  void *pData,                    /* Write data from this buffer */
  int nData                       /* Bytes of data to write */
){
  int rc = LSM_OK;
  PosixFile *p = (PosixFile *)pFile;
  off_t offset;

  offset = lseek(p->fd, (off_t)iOff, SEEK_SET);
  if( offset!=iOff ){
    rc = LSM_IOERR_BKPT;
  }else{
    ssize_t prc = write(p->fd, pData, (size_t)nData);
    if( prc<0 ) rc = LSM_IOERR_BKPT;
  }

  return rc;
}