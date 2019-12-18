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
 int /*<<< orphan*/  LSM_MUTEX_GLOBAL ; 
 int LSM_OK ; 
 int /*<<< orphan*/  lsmMutexEnter (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int lsmMutexStatic (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 

__attribute__((used)) static int enterGlobalMutex(lsm_env *pEnv){
  lsm_mutex *p;
  int rc = lsmMutexStatic(pEnv, LSM_MUTEX_GLOBAL, &p);
  if( rc==LSM_OK ) lsmMutexEnter(pEnv, p);
  return rc;
}