#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_file ;
struct TYPE_5__ {int /*<<< orphan*/  (* xClose ) (int /*<<< orphan*/ ) ;} ;
typedef  TYPE_1__ lsm_env ;
struct TYPE_6__ {int /*<<< orphan*/  pReal; } ;
typedef  TYPE_2__ LsmFile ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ) ; 
 TYPE_1__* tdb_lsm_env () ; 
 int /*<<< orphan*/  testFree (TYPE_2__*) ; 

__attribute__((used)) static int testEnvClose(lsm_file *pFile){
  lsm_env *pRealEnv = tdb_lsm_env();
  LsmFile *p = (LsmFile *)pFile;

  pRealEnv->xClose(p->pReal);
  testFree(p);
  return LSM_OK;
}