#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int (* xUnlink ) (TYPE_1__*,char const*) ;} ;
typedef  TYPE_1__ lsm_env ;

/* Variables and functions */
 int stub1 (TYPE_1__*,char const*) ; 
 TYPE_1__* tdb_lsm_env () ; 
 int /*<<< orphan*/  unused_parameter (TYPE_1__*) ; 

__attribute__((used)) static int testEnvUnlink(lsm_env *pEnv, const char *zFile){
  lsm_env *pRealEnv = tdb_lsm_env();
  unused_parameter(pEnv);
  return pRealEnv->xUnlink(pRealEnv, zFile);
}