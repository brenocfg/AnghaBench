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
struct TYPE_3__ {int (* xTestLock ) (int /*<<< orphan*/ *,int,int,int) ;} ;
typedef  TYPE_1__ lsm_env ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int,int,int) ; 

int lsmEnvTestLock(
  lsm_env *pEnv, 
  lsm_file *pFile, 
  int iLock, 
  int nLock, 
  int eLock
){
  return pEnv->xTestLock(pFile, iLock, nLock, eLock);
}