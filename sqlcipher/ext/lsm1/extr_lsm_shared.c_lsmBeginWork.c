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
typedef  int /*<<< orphan*/  lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_WORKER ; 
 int LSM_OK ; 
 int lsmCheckpointLoadWorker (int /*<<< orphan*/ *) ; 
 int lsmShmLock (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsmBeginWork(lsm_db *pDb){
  int rc;

  /* Attempt to take the WORKER lock */
  rc = lsmShmLock(pDb, LSM_LOCK_WORKER, LSM_LOCK_EXCL, 0);

  /* Deserialize the current worker snapshot */
  if( rc==LSM_OK ){
    rc = lsmCheckpointLoadWorker(pDb);
  }
  return rc;
}