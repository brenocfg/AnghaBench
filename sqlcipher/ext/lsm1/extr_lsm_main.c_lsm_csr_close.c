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
typedef  int /*<<< orphan*/  lsm_cursor ;
typedef  int /*<<< orphan*/  MultiCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int /*<<< orphan*/  assert_db_state (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dbReleaseClientSnapshot (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lsmMCursorClose (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lsmMCursorDb (int /*<<< orphan*/ *) ; 

int lsm_csr_close(lsm_cursor *p){
  if( p ){
    lsm_db *pDb = lsmMCursorDb((MultiCursor *)p);
    assert_db_state(pDb);
    lsmMCursorClose((MultiCursor *)p, 1);
    dbReleaseClientSnapshot(pDb);
    assert_db_state(pDb);
  }
  return LSM_OK;
}