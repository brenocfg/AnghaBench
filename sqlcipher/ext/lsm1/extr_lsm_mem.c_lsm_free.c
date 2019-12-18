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
typedef  int /*<<< orphan*/  lsm_env ;

/* Variables and functions */
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/ * lsm_default_env () ; 

void lsm_free(lsm_env *pEnv, void *p){
  lsmFree(pEnv ? pEnv : lsm_default_env(), p);
}