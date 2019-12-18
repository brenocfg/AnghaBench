#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_mutex ;
typedef  int /*<<< orphan*/  lsm_env ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/ * aStaticNoopMutex ; 
 scalar_t__ array_size (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int lsmPosixOsMutexStatic(
  lsm_env *pEnv,
  int iMutex,
  lsm_mutex **ppStatic
){
  assert( iMutex>=1 && iMutex<=(int)array_size(aStaticNoopMutex) );
  *ppStatic = (lsm_mutex *)&aStaticNoopMutex[iMutex-1];
  return LSM_OK;
}