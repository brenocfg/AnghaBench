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
struct TYPE_3__ {int (* xLock ) (int /*<<< orphan*/ *,int,int) ;} ;
typedef  TYPE_1__ lsm_env ;

/* Variables and functions */
 int LSM_OK ; 
 int stub1 (int /*<<< orphan*/ *,int,int) ; 

int lsmEnvLock(lsm_env *pEnv, lsm_file *pFile, int iLock, int eLock){
  if( pFile==0 ) return LSM_OK;
  return pEnv->xLock(pFile, iLock, eLock);
}