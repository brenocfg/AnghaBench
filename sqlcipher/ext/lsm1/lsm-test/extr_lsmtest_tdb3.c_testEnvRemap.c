#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_i64 ;
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_4__ {int (* xRemap ) (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ;} ;
typedef  TYPE_1__ lsm_env ;
struct TYPE_5__ {int /*<<< orphan*/  pReal; } ;
typedef  TYPE_2__ LsmFile ;

/* Variables and functions */
 int stub1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void**,int /*<<< orphan*/ *) ; 
 TYPE_1__* tdb_lsm_env () ; 

__attribute__((used)) static int testEnvRemap(
  lsm_file *pFile, 
  lsm_i64 iMin, 
  void **ppOut,
  lsm_i64 *pnOut
){
  lsm_env *pRealEnv = tdb_lsm_env();
  LsmFile *p = (LsmFile *)pFile;
  return pRealEnv->xRemap(p->pReal, iMin, ppOut, pnOut);
}