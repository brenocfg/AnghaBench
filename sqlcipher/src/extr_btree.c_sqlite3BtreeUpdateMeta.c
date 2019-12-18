#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_9__ {scalar_t__ incrVacuum; scalar_t__ autoVacuum; TYPE_1__* pPage1; } ;
struct TYPE_8__ {scalar_t__ inTrans; TYPE_3__* pBt; } ;
struct TYPE_7__ {unsigned char* aData; int /*<<< orphan*/  pDbPage; } ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 int BTREE_INCR_VACUUM ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  put4byte (unsigned char*,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_2__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_2__*) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 

int sqlite3BtreeUpdateMeta(Btree *p, int idx, u32 iMeta){
  BtShared *pBt = p->pBt;
  unsigned char *pP1;
  int rc;
  assert( idx>=1 && idx<=15 );
  sqlite3BtreeEnter(p);
  assert( p->inTrans==TRANS_WRITE );
  assert( pBt->pPage1!=0 );
  pP1 = pBt->pPage1->aData;
  rc = sqlite3PagerWrite(pBt->pPage1->pDbPage);
  if( rc==SQLITE_OK ){
    put4byte(&pP1[36 + idx*4], iMeta);
#ifndef SQLITE_OMIT_AUTOVACUUM
    if( idx==BTREE_INCR_VACUUM ){
      assert( pBt->autoVacuum || iMeta==0 );
      assert( iMeta==0 || iMeta==1 );
      pBt->incrVacuum = (u8)iMeta;
    }
#endif
  }
  sqlite3BtreeLeave(p);
  return rc;
}