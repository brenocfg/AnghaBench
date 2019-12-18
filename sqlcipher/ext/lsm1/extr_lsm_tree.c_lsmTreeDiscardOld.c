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
struct TYPE_5__ {scalar_t__ iOldShmid; scalar_t__ iUsedShmid; } ;
struct TYPE_6__ {TYPE_1__ treehdr; } ;
typedef  TYPE_2__ lsm_db ;

/* Variables and functions */
 int /*<<< orphan*/  LSM_LOCK_DMS2 ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_WRITER ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ lsmShmAssertLock (TYPE_2__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void lsmTreeDiscardOld(lsm_db *pDb){
  assert( lsmShmAssertLock(pDb, LSM_LOCK_WRITER, LSM_LOCK_EXCL) 
       || lsmShmAssertLock(pDb, LSM_LOCK_DMS2, LSM_LOCK_EXCL) 
  );
  pDb->treehdr.iUsedShmid = pDb->treehdr.iOldShmid;
  pDb->treehdr.iOldShmid = 0;
}