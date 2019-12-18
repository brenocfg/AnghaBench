#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_7__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_18__ {TYPE_3__* pBtree; struct TYPE_18__* pNext; } ;
struct TYPE_17__ {scalar_t__ wantToLock; scalar_t__ locked; TYPE_2__* pPrev; TYPE_1__* pNext; scalar_t__ pSchema; int /*<<< orphan*/  (* xFreeSchema ) (scalar_t__) ;TYPE_7__* db; int /*<<< orphan*/  pPager; TYPE_5__* pCursor; int /*<<< orphan*/  sharable; struct TYPE_17__* pBt; } ;
struct TYPE_16__ {TYPE_1__* pNext; } ;
struct TYPE_15__ {TYPE_2__* pPrev; } ;
typedef  TYPE_3__ Btree ;
typedef  TYPE_3__ BtShared ;
typedef  TYPE_5__ BtCursor ;

/* Variables and functions */
 int SQLITE_OK ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  freeTempSpace (TYPE_3__*) ; 
 scalar_t__ removeFromSharingList (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3BtreeCloseCursor (TYPE_5__*) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3BtreeRollback (TYPE_3__*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sqlite3PagerClose (int /*<<< orphan*/ ,TYPE_7__*) ; 
 int /*<<< orphan*/  sqlite3_free (TYPE_3__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (scalar_t__) ; 

int sqlite3BtreeClose(Btree *p){
  BtShared *pBt = p->pBt;
  BtCursor *pCur;

  /* Close all cursors opened via this handle.  */
  assert( sqlite3_mutex_held(p->db->mutex) );
  sqlite3BtreeEnter(p);
  pCur = pBt->pCursor;
  while( pCur ){
    BtCursor *pTmp = pCur;
    pCur = pCur->pNext;
    if( pTmp->pBtree==p ){
      sqlite3BtreeCloseCursor(pTmp);
    }
  }

  /* Rollback any active transaction and free the handle structure.
  ** The call to sqlite3BtreeRollback() drops any table-locks held by
  ** this handle.
  */
  sqlite3BtreeRollback(p, SQLITE_OK, 0);
  sqlite3BtreeLeave(p);

  /* If there are still other outstanding references to the shared-btree
  ** structure, return now. The remainder of this procedure cleans 
  ** up the shared-btree.
  */
  assert( p->wantToLock==0 && p->locked==0 );
  if( !p->sharable || removeFromSharingList(pBt) ){
    /* The pBt is no longer on the sharing list, so we can access
    ** it without having to hold the mutex.
    **
    ** Clean out and delete the BtShared object.
    */
    assert( !pBt->pCursor );
    sqlite3PagerClose(pBt->pPager, p->db);
    if( pBt->xFreeSchema && pBt->pSchema ){
      pBt->xFreeSchema(pBt->pSchema);
    }
    sqlite3DbFree(0, pBt->pSchema);
    freeTempSpace(pBt);
    sqlite3_free(pBt);
  }

#ifndef SQLITE_OMIT_SHARED_CACHE
  assert( p->wantToLock==0 );
  assert( p->locked==0 );
  if( p->pPrev ) p->pPrev->pNext = p->pNext;
  if( p->pNext ) p->pNext->pPrev = p->pPrev;
#endif

  sqlite3_free(p);
  return SQLITE_OK;
}