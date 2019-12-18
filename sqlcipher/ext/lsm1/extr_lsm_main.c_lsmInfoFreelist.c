#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pEnv; } ;
typedef  TYPE_1__ lsm_db ;
struct TYPE_10__ {char* z; } ;
typedef  int /*<<< orphan*/  Snapshot ;
typedef  TYPE_2__ LsmString ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  infoFreeWorker (TYPE_1__*,int) ; 
 int /*<<< orphan*/  infoFreelistCb ; 
 int infoGetWorker (TYPE_1__*,int /*<<< orphan*/ **,int*) ; 
 int /*<<< orphan*/  lsmFree (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  lsmStringInit (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lsmWalkFreelist (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 

int lsmInfoFreelist(lsm_db *pDb, char **pzOut){
  Snapshot *pWorker;              /* Worker snapshot */
  int bUnlock = 0;
  LsmString s;
  int rc;

  /* Obtain the worker snapshot */
  rc = infoGetWorker(pDb, &pWorker, &bUnlock);
  if( rc!=LSM_OK ) return rc;

  lsmStringInit(&s, pDb->pEnv);
  rc = lsmWalkFreelist(pDb, 0, infoFreelistCb, &s);
  if( rc!=LSM_OK ){
    lsmFree(pDb->pEnv, s.z);
  }else{
    *pzOut = s.z;
  }

  /* Release the snapshot and return */
  infoFreeWorker(pDb, bUnlock);
  return rc;
}