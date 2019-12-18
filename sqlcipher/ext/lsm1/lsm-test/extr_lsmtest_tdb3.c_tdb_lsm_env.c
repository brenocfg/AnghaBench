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
typedef  int /*<<< orphan*/  env ;

/* Variables and functions */
 int /*<<< orphan*/  lsm_default_env () ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

lsm_env *tdb_lsm_env(void){
  static int bInit = 0;
  static lsm_env env;
  if( bInit==0 ){
    memcpy(&env, lsm_default_env(), sizeof(env));
    bInit = 1;
  }
  return &env;
}