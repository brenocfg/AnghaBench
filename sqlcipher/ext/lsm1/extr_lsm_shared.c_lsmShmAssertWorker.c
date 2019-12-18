#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ pWorker; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_WORKER ; 
 scalar_t__ lsmShmAssertLock (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int lsmShmAssertWorker(lsm_db *db){
  return lsmShmAssertLock(db, LSM_LOCK_WORKER, LSM_LOCK_EXCL) && db->pWorker;
}