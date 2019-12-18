#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  pPager; int /*<<< orphan*/  nPage; scalar_t__ bDoTruncate; scalar_t__ autoVacuum; } ;
struct TYPE_7__ {scalar_t__ inTrans; TYPE_2__* pBt; } ;
typedef  TYPE_1__ Btree ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int SQLITE_OK ; 
 scalar_t__ TRANS_WRITE ; 
 int autoVacuumCommit (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_1__*) ; 
 int sqlite3PagerCommitPhaseOne (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerTruncateImage (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int sqlite3BtreeCommitPhaseOne(Btree *p, const char *zMaster){
  int rc = SQLITE_OK;
  if( p->inTrans==TRANS_WRITE ){
    BtShared *pBt = p->pBt;
    sqlite3BtreeEnter(p);
#ifndef SQLITE_OMIT_AUTOVACUUM
    if( pBt->autoVacuum ){
      rc = autoVacuumCommit(pBt);
      if( rc!=SQLITE_OK ){
        sqlite3BtreeLeave(p);
        return rc;
      }
    }
    if( pBt->bDoTruncate ){
      sqlite3PagerTruncateImage(pBt->pPager, pBt->nPage);
    }
#endif
    rc = sqlite3PagerCommitPhaseOne(pBt->pPager, zMaster, 0);
    sqlite3BtreeLeave(p);
  }
  return rc;
}