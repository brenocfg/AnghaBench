#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
struct TYPE_12__ {int flags; } ;
typedef  TYPE_1__ TreeKey ;
struct TYPE_14__ {int /*<<< orphan*/  member_1; int /*<<< orphan*/  member_0; } ;
struct TYPE_13__ {int /*<<< orphan*/  pDb; TYPE_3__ blob; } ;
typedef  TYPE_2__ TreeCursor ;
typedef  TYPE_3__ TreeBlob ;

/* Variables and functions */
 int LSM_END_DELETE ; 
 int LSM_OK ; 
 int LSM_START_DELETE ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_1__* csrGetKey (TYPE_2__*,TYPE_3__*,int*) ; 
 int lsmTreeCursorEnd (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int lsmTreeCursorNext (TYPE_2__*) ; 
 scalar_t__ lsmTreeCursorValid (TYPE_2__*) ; 
 int /*<<< orphan*/  tblobFree (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  treeCursorInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static int assert_delete_ranges_match(lsm_db *db){
  int prev = 0;
  TreeBlob blob = {0, 0};
  TreeCursor csr;               /* Cursor used to iterate through tree */
  int rc;

  treeCursorInit(db, 0, &csr);
  for( rc = lsmTreeCursorEnd(&csr, 0);
       rc==LSM_OK && lsmTreeCursorValid(&csr);
       rc = lsmTreeCursorNext(&csr)
  ){
    TreeKey *pKey = csrGetKey(&csr, &blob, &rc);
    if( rc!=LSM_OK ) break;
    assert( ((prev&LSM_START_DELETE)==0)==((pKey->flags&LSM_END_DELETE)==0) );
    prev = pKey->flags;
  }

  tblobFree(csr.pDb, &csr.blob);
  tblobFree(csr.pDb, &blob);

  return 1;
}