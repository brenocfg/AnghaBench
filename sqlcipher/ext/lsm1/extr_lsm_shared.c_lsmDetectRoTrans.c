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
struct TYPE_4__ {scalar_t__ bReadonly; } ;
typedef  TYPE_1__ lsm_db ;

/* Variables and functions */
 int LSM_BUSY ; 
 int /*<<< orphan*/  LSM_LOCK_EXCL ; 
 int /*<<< orphan*/  LSM_LOCK_ROTRANS ; 
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int lsmShmTestLock (TYPE_1__*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

int lsmDetectRoTrans(lsm_db *db, int *pbExist){
  int rc;

  /* Only a read-write connection may use this function. */
  assert( db->bReadonly==0 );

  rc = lsmShmTestLock(db, LSM_LOCK_ROTRANS, 1, LSM_LOCK_EXCL);
  if( rc==LSM_BUSY ){
    *pbExist = 1;
    rc = LSM_OK;
  }else{
    *pbExist = 0;
  }

  return rc;
}