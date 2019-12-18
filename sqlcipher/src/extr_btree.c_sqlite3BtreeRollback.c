#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_18__ {scalar_t__ inTransaction; int nPage; int /*<<< orphan*/  pPager; } ;
struct TYPE_17__ {scalar_t__ inTrans; TYPE_3__* pBt; } ;
struct TYPE_16__ {scalar_t__ aData; } ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 int SQLITE_ABORT_ROLLBACK ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_READ ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeClearHasContent (TYPE_3__*) ; 
 int /*<<< orphan*/  btreeEndTransaction (TYPE_2__*) ; 
 int btreeGetPage (TYPE_3__*,int,TYPE_1__**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  btreeIntegrity (TYPE_2__*) ; 
 scalar_t__ countValidCursors (TYPE_3__*,int) ; 
 int get4byte (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  releasePageOne (TYPE_1__*) ; 
 int saveAllCursors (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_2__*) ; 
 int sqlite3BtreeTripAllCursors (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  sqlite3PagerPagecount (int /*<<< orphan*/ ,int*) ; 
 int sqlite3PagerRollback (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

int sqlite3BtreeRollback(Btree *p, int tripCode, int writeOnly){
  int rc;
  BtShared *pBt = p->pBt;
  MemPage *pPage1;

  assert( writeOnly==1 || writeOnly==0 );
  assert( tripCode==SQLITE_ABORT_ROLLBACK || tripCode==SQLITE_OK );
  sqlite3BtreeEnter(p);
  if( tripCode==SQLITE_OK ){
    rc = tripCode = saveAllCursors(pBt, 0, 0);
    if( rc ) writeOnly = 0;
  }else{
    rc = SQLITE_OK;
  }
  if( tripCode ){
    int rc2 = sqlite3BtreeTripAllCursors(p, tripCode, writeOnly);
    assert( rc==SQLITE_OK || (writeOnly==0 && rc2==SQLITE_OK) );
    if( rc2!=SQLITE_OK ) rc = rc2;
  }
  btreeIntegrity(p);

  if( p->inTrans==TRANS_WRITE ){
    int rc2;

    assert( TRANS_WRITE==pBt->inTransaction );
    rc2 = sqlite3PagerRollback(pBt->pPager);
    if( rc2!=SQLITE_OK ){
      rc = rc2;
    }

    /* The rollback may have destroyed the pPage1->aData value.  So
    ** call btreeGetPage() on page 1 again to make
    ** sure pPage1->aData is set correctly. */
    if( btreeGetPage(pBt, 1, &pPage1, 0)==SQLITE_OK ){
      int nPage = get4byte(28+(u8*)pPage1->aData);
      testcase( nPage==0 );
      if( nPage==0 ) sqlite3PagerPagecount(pBt->pPager, &nPage);
      testcase( pBt->nPage!=nPage );
      pBt->nPage = nPage;
      releasePageOne(pPage1);
    }
    assert( countValidCursors(pBt, 1)==0 );
    pBt->inTransaction = TRANS_READ;
    btreeClearHasContent(pBt);
  }

  btreeEndTransaction(p);
  sqlite3BtreeLeave(p);
  return rc;
}