#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct KeyInfo {int dummy; } ;
struct TYPE_15__ {scalar_t__ pgnoRoot; int iPage; int /*<<< orphan*/  eState; struct TYPE_15__* pNext; int /*<<< orphan*/  curFlags; int /*<<< orphan*/  curPagerFlags; TYPE_3__* pBt; TYPE_2__* pBtree; struct KeyInfo* pKeyInfo; } ;
struct TYPE_14__ {int btsFlags; scalar_t__ pTmpSpace; TYPE_4__* pCursor; TYPE_1__* pPage1; } ;
struct TYPE_13__ {scalar_t__ inTrans; TYPE_3__* pBt; } ;
struct TYPE_12__ {scalar_t__ aData; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_2__ Btree ;
typedef  TYPE_3__ BtShared ;
typedef  TYPE_4__ BtCursor ;

/* Variables and functions */
 int /*<<< orphan*/  BTCF_Multiple ; 
 int /*<<< orphan*/  BTCF_WriteFlag ; 
 int BTREE_FORDELETE ; 
 int BTREE_WRCSR ; 
 int BTS_READ_ONLY ; 
 int /*<<< orphan*/  CURSOR_INVALID ; 
 int /*<<< orphan*/  PAGER_GET_READONLY ; 
 int SQLITE_NOMEM_BKPT ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_NONE ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  allocateTempSpace (TYPE_3__*) ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ btreePagecount (TYPE_3__*) ; 
 int /*<<< orphan*/  hasReadConflicts (TYPE_2__*,int) ; 
 int hasSharedCacheTableLock (TYPE_2__*,int,int,int) ; 
 int sqlite3BtreeHoldsMutex (TYPE_2__*) ; 

__attribute__((used)) static int btreeCursor(
  Btree *p,                              /* The btree */
  int iTable,                            /* Root page of table to open */
  int wrFlag,                            /* 1 to write. 0 read-only */
  struct KeyInfo *pKeyInfo,              /* First arg to comparison function */
  BtCursor *pCur                         /* Space for new cursor */
){
  BtShared *pBt = p->pBt;                /* Shared b-tree handle */
  BtCursor *pX;                          /* Looping over other all cursors */

  assert( sqlite3BtreeHoldsMutex(p) );
  assert( wrFlag==0 
       || wrFlag==BTREE_WRCSR 
       || wrFlag==(BTREE_WRCSR|BTREE_FORDELETE) 
  );

  /* The following assert statements verify that if this is a sharable 
  ** b-tree database, the connection is holding the required table locks, 
  ** and that no other connection has any open cursor that conflicts with 
  ** this lock.  */
  assert( hasSharedCacheTableLock(p, iTable, pKeyInfo!=0, (wrFlag?2:1)) );
  assert( wrFlag==0 || !hasReadConflicts(p, iTable) );

  /* Assert that the caller has opened the required transaction. */
  assert( p->inTrans>TRANS_NONE );
  assert( wrFlag==0 || p->inTrans==TRANS_WRITE );
  assert( pBt->pPage1 && pBt->pPage1->aData );
  assert( wrFlag==0 || (pBt->btsFlags & BTS_READ_ONLY)==0 );

  if( wrFlag ){
    allocateTempSpace(pBt);
    if( pBt->pTmpSpace==0 ) return SQLITE_NOMEM_BKPT;
  }
  if( iTable==1 && btreePagecount(pBt)==0 ){
    assert( wrFlag==0 );
    iTable = 0;
  }

  /* Now that no other errors can occur, finish filling in the BtCursor
  ** variables and link the cursor into the BtShared list.  */
  pCur->pgnoRoot = (Pgno)iTable;
  pCur->iPage = -1;
  pCur->pKeyInfo = pKeyInfo;
  pCur->pBtree = p;
  pCur->pBt = pBt;
  pCur->curFlags = wrFlag ? BTCF_WriteFlag : 0;
  pCur->curPagerFlags = wrFlag ? 0 : PAGER_GET_READONLY;
  /* If there are two or more cursors on the same btree, then all such
  ** cursors *must* have the BTCF_Multiple flag set. */
  for(pX=pBt->pCursor; pX; pX=pX->pNext){
    if( pX->pgnoRoot==(Pgno)iTable ){
      pX->curFlags |= BTCF_Multiple;
      pCur->curFlags |= BTCF_Multiple;
    }
  }
  pCur->pNext = pBt->pCursor;
  pBt->pCursor = pCur;
  pCur->eState = CURSOR_INVALID;
  return SQLITE_OK;
}