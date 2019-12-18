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
struct TYPE_3__ {int (* xRemap ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ lsm_env ;
typedef  int /*<<< orphan*/  i64 ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int lsmEnvRemap(
  lsm_env *pEnv, 
  lsm_file *pFile, 
  i64 szMin,
  void **ppMap,
  i64 *pszMap
){
  return pEnv->xRemap(pFile, szMin, ppMap, pszMap);
}