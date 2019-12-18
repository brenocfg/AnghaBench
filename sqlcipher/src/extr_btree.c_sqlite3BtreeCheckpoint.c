#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ inTransaction; int /*<<< orphan*/  pPager; } ;
struct TYPE_6__ {int /*<<< orphan*/  db; TYPE_2__* pBt; } ;
typedef  TYPE_1__ Btree ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 int SQLITE_LOCKED ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_NONE ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_1__*) ; 
 int sqlite3PagerCheckpoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int*,int*) ; 

int sqlite3BtreeCheckpoint(Btree *p, int eMode, int *pnLog, int *pnCkpt){
  int rc = SQLITE_OK;
  if( p ){
    BtShared *pBt = p->pBt;
    sqlite3BtreeEnter(p);
    if( pBt->inTransaction!=TRANS_NONE ){
      rc = SQLITE_LOCKED;
    }else{
      rc = sqlite3PagerCheckpoint(pBt->pPager, p->db, eMode, pnLog, pnCkpt);
    }
    sqlite3BtreeLeave(p);
  }
  return rc;
}