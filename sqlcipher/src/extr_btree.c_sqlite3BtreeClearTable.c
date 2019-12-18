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
struct TYPE_6__ {scalar_t__ inTrans; int /*<<< orphan*/ * pBt; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_1__ Btree ;
typedef  int /*<<< orphan*/  BtShared ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int clearDatabasePage (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  invalidateIncrblobCursors (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int saveAllCursors (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_1__*) ; 

int sqlite3BtreeClearTable(Btree *p, int iTable, int *pnChange){
  int rc;
  BtShared *pBt = p->pBt;
  sqlite3BtreeEnter(p);
  assert( p->inTrans==TRANS_WRITE );

  rc = saveAllCursors(pBt, (Pgno)iTable, 0);

  if( SQLITE_OK==rc ){
    /* Invalidate all incrblob cursors open on table iTable (assuming iTable
    ** is the root of a table b-tree - if it is not, the following call is
    ** a no-op).  */
    invalidateIncrblobCursors(p, (Pgno)iTable, 0, 1);
    rc = clearDatabasePage(pBt, (Pgno)iTable, 0, pnChange);
  }
  sqlite3BtreeLeave(p);
  return rc;
}