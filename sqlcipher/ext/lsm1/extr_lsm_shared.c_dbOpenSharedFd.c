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
typedef  int /*<<< orphan*/  lsm_env ;
struct TYPE_3__ {int bReadonly; int /*<<< orphan*/  pFile; int /*<<< orphan*/  zName; } ;
typedef  TYPE_1__ Database ;

/* Variables and functions */
 int LSM_IOERR ; 
 int /*<<< orphan*/  LSM_OPEN_READONLY ; 
 int lsmEnvOpen (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int dbOpenSharedFd(lsm_env *pEnv, Database *p, int bRoOk){
  int rc;

  rc = lsmEnvOpen(pEnv, p->zName, 0, &p->pFile);
  if( rc==LSM_IOERR && bRoOk ){
    rc = lsmEnvOpen(pEnv, p->zName, LSM_OPEN_READONLY, &p->pFile);
    p->bReadonly = 1;
  }

  return rc;
}