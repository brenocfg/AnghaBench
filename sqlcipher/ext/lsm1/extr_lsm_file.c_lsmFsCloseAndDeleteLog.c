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
struct TYPE_3__ {int /*<<< orphan*/  pEnv; int /*<<< orphan*/  zDb; scalar_t__ fdLog; } ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  lsmEnvClose (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  lsmEnvUnlink (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 char* lsmMallocPrintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 

int lsmFsCloseAndDeleteLog(FileSystem *pFS){
  char *zDel;

  if( pFS->fdLog ){
    lsmEnvClose(pFS->pEnv, pFS->fdLog );
    pFS->fdLog = 0;
  }

  zDel = lsmMallocPrintf(pFS->pEnv, "%s-log", pFS->zDb);
  if( zDel ){
    lsmEnvUnlink(pFS->pEnv, zDel);
    lsmFree(pFS->pEnv, zDel);
  }
  return LSM_OK;
}