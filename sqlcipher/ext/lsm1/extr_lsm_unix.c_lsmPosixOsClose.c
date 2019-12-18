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
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_3__ {int /*<<< orphan*/  pEnv; struct TYPE_3__* apShm; int /*<<< orphan*/  fd; int /*<<< orphan*/  nMap; scalar_t__ pMap; } ;
typedef  TYPE_1__ PosixFile ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  close (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsmPosixOsShmUnmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lsm_free (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  munmap (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lsmPosixOsClose(lsm_file *pFile){
   PosixFile *p = (PosixFile *)pFile;
   lsmPosixOsShmUnmap(pFile, 0);
   if( p->pMap ) munmap(p->pMap, p->nMap);
   close(p->fd);
   lsm_free(p->pEnv, p->apShm);
   lsm_free(p->pEnv, p);
   return LSM_OK;
}