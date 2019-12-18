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
struct stat {scalar_t__ st_size; } ;
typedef  int /*<<< orphan*/  off_t ;
typedef  scalar_t__ lsm_i64 ;
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_2__ {int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int LSM_IOERR_BKPT ; 
 int LSM_OK ; 
 int fstat (int /*<<< orphan*/ ,struct stat*) ; 
 int ftruncate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsmPosixOsTruncate(
  lsm_file *pFile,                /* File to write to */
  lsm_i64 nSize                   /* Size to truncate file to */
){
  PosixFile *p = (PosixFile *)pFile;
  int rc = LSM_OK;                /* Return code */
  int prc;                        /* Posix Return Code */
  struct stat sStat;              /* Result of fstat() invocation */
  
  prc = fstat(p->fd, &sStat);
  if( prc==0 && sStat.st_size>nSize ){
    prc = ftruncate(p->fd, (off_t)nSize);
  }
  if( prc<0 ) rc = LSM_IOERR_BKPT;

  return rc;
}