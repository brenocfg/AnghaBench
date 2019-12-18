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
struct TYPE_14__ {scalar_t__ inTransaction; int /*<<< orphan*/  nPage; TYPE_1__* pPage1; int /*<<< orphan*/  autoVacuum; } ;
struct TYPE_13__ {scalar_t__ inTrans; TYPE_3__* pBt; } ;
struct TYPE_12__ {int /*<<< orphan*/ * aData; int /*<<< orphan*/  pDbPage; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_DONE ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ btreePagecount (TYPE_3__*) ; 
 scalar_t__ finalDbSize (TYPE_3__*,scalar_t__,scalar_t__) ; 
 scalar_t__ get4byte (int /*<<< orphan*/ *) ; 
 int incrVacuumStep (TYPE_3__*,scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  invalidateAllOverflowCache (TYPE_3__*) ; 
 int /*<<< orphan*/  put4byte (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int saveAllCursors (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_2__*) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 

int sqlite3BtreeIncrVacuum(Btree *p){
  int rc;
  BtShared *pBt = p->pBt;

  sqlite3BtreeEnter(p);
  assert( pBt->inTransaction==TRANS_WRITE && p->inTrans==TRANS_WRITE );
  if( !pBt->autoVacuum ){
    rc = SQLITE_DONE;
  }else{
    Pgno nOrig = btreePagecount(pBt);
    Pgno nFree = get4byte(&pBt->pPage1->aData[36]);
    Pgno nFin = finalDbSize(pBt, nOrig, nFree);

    if( nOrig<nFin ){
      rc = SQLITE_CORRUPT_BKPT;
    }else if( nFree>0 ){
      rc = saveAllCursors(pBt, 0, 0);
      if( rc==SQLITE_OK ){
        invalidateAllOverflowCache(pBt);
        rc = incrVacuumStep(pBt, nFin, nOrig, 0);
      }
      if( rc==SQLITE_OK ){
        rc = sqlite3PagerWrite(pBt->pPage1->pDbPage);
        put4byte(&pBt->pPage1->aData[28], pBt->nPage);
      }
    }else{
      rc = SQLITE_DONE;
    }
  }
  sqlite3BtreeLeave(p);
  return rc;
}