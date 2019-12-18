#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ inTransaction; scalar_t__ nTransaction; int /*<<< orphan*/  pPager; } ;
struct TYPE_9__ {scalar_t__ inTrans; int /*<<< orphan*/  iDataVersion; TYPE_2__* pBt; } ;
typedef  TYPE_1__ Btree ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ TRANS_NONE ; 
 scalar_t__ TRANS_READ ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeClearHasContent (TYPE_2__*) ; 
 int /*<<< orphan*/  btreeEndTransaction (TYPE_1__*) ; 
 int /*<<< orphan*/  btreeIntegrity (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_1__*) ; 
 int sqlite3PagerCommitPhaseTwo (int /*<<< orphan*/ ) ; 

int sqlite3BtreeCommitPhaseTwo(Btree *p, int bCleanup){

  if( p->inTrans==TRANS_NONE ) return SQLITE_OK;
  sqlite3BtreeEnter(p);
  btreeIntegrity(p);

  /* If the handle has a write-transaction open, commit the shared-btrees 
  ** transaction and set the shared state to TRANS_READ.
  */
  if( p->inTrans==TRANS_WRITE ){
    int rc;
    BtShared *pBt = p->pBt;
    assert( pBt->inTransaction==TRANS_WRITE );
    assert( pBt->nTransaction>0 );
    rc = sqlite3PagerCommitPhaseTwo(pBt->pPager);
    if( rc!=SQLITE_OK && bCleanup==0 ){
      sqlite3BtreeLeave(p);
      return rc;
    }
    p->iDataVersion--;  /* Compensate for pPager->iDataVersion++; */
    pBt->inTransaction = TRANS_READ;
    btreeClearHasContent(pBt);
  }

  btreeEndTransaction(p);
  sqlite3BtreeLeave(p);
  return SQLITE_OK;
}