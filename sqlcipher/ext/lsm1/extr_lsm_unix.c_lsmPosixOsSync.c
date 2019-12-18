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
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_2__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  nMap; scalar_t__ pMap; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int LSM_IOERR_BKPT ; 
 int LSM_OK ; 
 int /*<<< orphan*/  MS_SYNC ; 
 int fdatasync (int /*<<< orphan*/ ) ; 
 int msync (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsmPosixOsSync(lsm_file *pFile){
  int rc = LSM_OK;

#ifndef LSM_NO_SYNC
  PosixFile *p = (PosixFile *)pFile;
  int prc = 0;

  if( p->pMap ){
    prc = msync(p->pMap, p->nMap, MS_SYNC);
  }
  if( prc==0 ) prc = fdatasync(p->fd);
  if( prc<0 ) rc = LSM_IOERR_BKPT;
#else
  (void)pFile;
#endif

  return rc;
}