#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lsm_db ;
struct TYPE_6__ {int /*<<< orphan*/  blob; int /*<<< orphan*/  pDb; } ;
typedef  TYPE_1__ TreeCursor ;

/* Variables and functions */
 int LSM_OK ; 
 int lsmTreeCursorEnd (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int lsmTreeCursorNext (TYPE_1__*) ; 
 scalar_t__ lsmTreeCursorValid (TYPE_1__*) ; 
 int /*<<< orphan*/  tblobFree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  treeCursorInit (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static int treeCountEntries(lsm_db *db){
  TreeCursor csr;               /* Cursor used to iterate through tree */
  int rc;
  int nEntry = 0;

  treeCursorInit(db, 0, &csr);
  for( rc = lsmTreeCursorEnd(&csr, 0);
       rc==LSM_OK && lsmTreeCursorValid(&csr);
       rc = lsmTreeCursorNext(&csr)
  ){
    nEntry++;
  }

  tblobFree(csr.pDb, &csr.blob);

  return nEntry;
}