#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ pShmhdr; scalar_t__ iReader; int /*<<< orphan*/  bReadonly; } ;
typedef  TYPE_1__ lsm_db ;
typedef  int /*<<< orphan*/  lsm_cursor ;
typedef  int /*<<< orphan*/  MultiCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_db_state (TYPE_1__*) ; 
 int /*<<< orphan*/  dbReleaseClientSnapshot (TYPE_1__*) ; 
 int lsmBeginReadTrans (TYPE_1__*) ; 
 int lsmBeginRoTrans (TYPE_1__*) ; 
 int /*<<< orphan*/  lsmMCursorClose (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int lsmMCursorNew (TYPE_1__*,int /*<<< orphan*/ **) ; 

int lsm_csr_open(lsm_db *pDb, lsm_cursor **ppCsr){
  int rc = LSM_OK;                /* Return code */
  MultiCursor *pCsr = 0;          /* New cursor object */

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
    rc = lsmMCursorNew(pDb, &pCsr);
  }

  /* If an error has occured, set the output to NULL and delete any partially
  ** allocated cursor. If this means there are no open cursors, release the
  ** client snapshot.  */
  if( rc!=LSM_OK ){
    lsmMCursorClose(pCsr, 0);
    dbReleaseClientSnapshot(pDb);
  }

  assert_db_state(pDb);
  *ppCsr = (lsm_cursor *)pCsr;
  return rc;
}