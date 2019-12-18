#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {unsigned int iUsrVersion; } ;
struct TYPE_9__ {scalar_t__ pShmhdr; scalar_t__ iReader; TYPE_1__ treehdr; int /*<<< orphan*/  bReadonly; } ;
typedef  TYPE_2__ lsm_db ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_db_state (TYPE_2__*) ; 
 int /*<<< orphan*/  dbReleaseClientSnapshot (TYPE_2__*) ; 
 int lsmBeginReadTrans (TYPE_2__*) ; 
 int lsmBeginRoTrans (TYPE_2__*) ; 

int lsm_get_user_version(lsm_db *pDb, unsigned int *piUsr){
  int rc = LSM_OK;                /* Return code */

  /* Open a read transaction if one is not already open. */
  assert_db_state(pDb);
  if( pDb->pShmhdr==0 ){
    assert( pDb->bReadonly );
    rc = lsmBeginRoTrans(pDb);
  }else if( pDb->iReader<0 ){
    rc = lsmBeginReadTrans(pDb);
  }

  /* Allocate the multi-cursor. */
  if( rc==LSM_OK ){
    *piUsr = pDb->treehdr.iUsrVersion;
  }

  dbReleaseClientSnapshot(pDb);
  assert_db_state(pDb);
  return rc;
}