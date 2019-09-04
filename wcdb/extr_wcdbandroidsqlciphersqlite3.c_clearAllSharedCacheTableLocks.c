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
struct TYPE_9__ {scalar_t__ eLock; int iTable; struct TYPE_9__* pNext; TYPE_1__* pBtree; } ;
struct TYPE_8__ {int btsFlags; int nTransaction; TYPE_1__* pWriter; TYPE_3__* pLock; } ;
struct TYPE_7__ {scalar_t__ inTrans; TYPE_3__ lock; scalar_t__ sharable; TYPE_2__* pBt; } ;
typedef  TYPE_1__ Btree ;
typedef  TYPE_2__ BtShared ;
typedef  TYPE_3__ BtLock ;

/* Variables and functions */
 int BTS_EXCLUSIVE ; 
 int BTS_PENDING ; 
 int /*<<< orphan*/  assert (int) ; 
 int sqlite3BtreeHoldsMutex (TYPE_1__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 

__attribute__((used)) static void clearAllSharedCacheTableLocks(Btree *p){
  BtShared *pBt = p->pBt;
  BtLock **ppIter = &pBt->pLock;

  assert( sqlite3BtreeHoldsMutex(p) );
  assert( p->sharable || 0==*ppIter );
  assert( p->inTrans>0 );

  while( *ppIter ){
    BtLock *pLock = *ppIter;
    assert( (pBt->btsFlags & BTS_EXCLUSIVE)==0 || pBt->pWriter==pLock->pBtree );
    assert( pLock->pBtree->inTrans>=pLock->eLock );
    if( pLock->pBtree==p ){
      *ppIter = pLock->pNext;
      assert( pLock->iTable!=1 || pLock==&p->lock );
      if( pLock->iTable!=1 ){
        sqlite3_free(pLock);
      }
    }else{
      ppIter = &pLock->pNext;
    }
  }

  assert( (pBt->btsFlags & BTS_PENDING)==0 || pBt->pWriter );
  if( pBt->pWriter==p ){
    pBt->pWriter = 0;
    pBt->btsFlags &= ~(BTS_EXCLUSIVE|BTS_PENDING);
  }else if( pBt->nTransaction==2 ){
    /* This function is called when Btree p is concluding its 
    ** transaction. If there currently exists a writer, and p is not
    ** that writer, then the number of locks held by connections other
    ** than the writer must be about to drop to zero. In this case
    ** set the BTS_PENDING flag to 0.
    **
    ** If there is not currently a writer, then BTS_PENDING must
    ** be zero already. So this next line is harmless in that case.
    */
    pBt->btsFlags &= ~BTS_PENDING;
  }
}