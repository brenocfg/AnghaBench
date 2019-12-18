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
struct TYPE_3__ {int /*<<< orphan*/  nMap; int /*<<< orphan*/  pMap; int /*<<< orphan*/  fdDb; int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ FileSystem ;

/* Variables and functions */
 int LSM_OK ; 
 int lsmEnvRemap (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

int lsmFsUnmap(FileSystem *pFS){
  int rc = LSM_OK;
  if( pFS ){
    rc = lsmEnvRemap(pFS->pEnv, pFS->fdDb, -1, &pFS->pMap, &pFS->nMap);
  }
  return rc;
}