#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct TYPE_18__ {int flags; int /*<<< orphan*/  nSavepoint; } ;
typedef  TYPE_1__ sqlite3 ;
struct TYPE_22__ {int iTable; struct TYPE_22__* pNext; int /*<<< orphan*/  eLock; TYPE_3__* pBtree; } ;
struct TYPE_21__ {scalar_t__ inTransaction; int btsFlags; scalar_t__ nPage; int /*<<< orphan*/  pPager; TYPE_2__* pPage1; TYPE_3__* pWriter; TYPE_5__* pLock; int /*<<< orphan*/  nTransaction; int /*<<< orphan*/  bDoTruncate; } ;
struct TYPE_20__ {scalar_t__ inTrans; TYPE_1__* db; TYPE_5__ lock; scalar_t__ sharable; TYPE_4__* pBt; } ;
struct TYPE_19__ {int /*<<< orphan*/ * aData; int /*<<< orphan*/  pDbPage; } ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ Btree ;
typedef  TYPE_4__ BtShared ;
typedef  TYPE_5__ BtLock ;

/* Variables and functions */
 int BTS_EXCLUSIVE ; 
 int BTS_INITIALLY_EMPTY ; 
 int BTS_PENDING ; 
 int BTS_READ_ONLY ; 
 scalar_t__ IfNotOmitAV (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MASTER_ROOT ; 
 int /*<<< orphan*/  READ_LOCK ; 
 int SQLITE_BUSY ; 
 int SQLITE_BUSY_SNAPSHOT ; 
 int SQLITE_LOCKED_SHAREDCACHE ; 
 int SQLITE_OK ; 
 int SQLITE_READONLY ; 
 int SQLITE_ResetDatabase ; 
 scalar_t__ TRANS_NONE ; 
 scalar_t__ TRANS_READ ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeIntegrity (TYPE_3__*) ; 
 scalar_t__ btreeInvokeBusyHandler (TYPE_4__*) ; 
 scalar_t__ get4byte (int /*<<< orphan*/ *) ; 
 int lockBtree (TYPE_4__*) ; 
 int newDatabase (TYPE_4__*) ; 
 int /*<<< orphan*/  put4byte (int /*<<< orphan*/ *,scalar_t__) ; 
 int querySharedCacheTableLock (TYPE_3__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3BtreeEnter (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3BtreeLeave (TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3ConnectionBlocked (TYPE_1__*,TYPE_1__*) ; 
 int sqlite3PagerBegin (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 scalar_t__ sqlite3PagerIsreadonly (int /*<<< orphan*/ ) ; 
 int sqlite3PagerOpenSavepoint (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3PagerResetLockTimeout (int /*<<< orphan*/ ) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3TempInMemory (TYPE_1__*) ; 
 int /*<<< orphan*/  unlockBtreeIfUnused (TYPE_4__*) ; 

int sqlite3BtreeBeginTrans(Btree *p, int wrflag, int *pSchemaVersion){
  BtShared *pBt = p->pBt;
  int rc = SQLITE_OK;

  sqlite3BtreeEnter(p);
  btreeIntegrity(p);

  /* If the btree is already in a write-transaction, or it
  ** is already in a read-transaction and a read-transaction
  ** is requested, this is a no-op.
  */
  if( p->inTrans==TRANS_WRITE || (p->inTrans==TRANS_READ && !wrflag) ){
    goto trans_begun;
  }
  assert( pBt->inTransaction==TRANS_WRITE || IfNotOmitAV(pBt->bDoTruncate)==0 );

  if( (p->db->flags & SQLITE_ResetDatabase) 
   && sqlite3PagerIsreadonly(pBt->pPager)==0 
  ){
    pBt->btsFlags &= ~BTS_READ_ONLY;
  }

  /* Write transactions are not possible on a read-only database */
  if( (pBt->btsFlags & BTS_READ_ONLY)!=0 && wrflag ){
    rc = SQLITE_READONLY;
    goto trans_begun;
  }

#ifndef SQLITE_OMIT_SHARED_CACHE
  {
    sqlite3 *pBlock = 0;
    /* If another database handle has already opened a write transaction 
    ** on this shared-btree structure and a second write transaction is
    ** requested, return SQLITE_LOCKED.
    */
    if( (wrflag && pBt->inTransaction==TRANS_WRITE)
     || (pBt->btsFlags & BTS_PENDING)!=0
    ){
      pBlock = pBt->pWriter->db;
    }else if( wrflag>1 ){
      BtLock *pIter;
      for(pIter=pBt->pLock; pIter; pIter=pIter->pNext){
        if( pIter->pBtree!=p ){
          pBlock = pIter->pBtree->db;
          break;
        }
      }
    }
    if( pBlock ){
      sqlite3ConnectionBlocked(p->db, pBlock);
      rc = SQLITE_LOCKED_SHAREDCACHE;
      goto trans_begun;
    }
  }
#endif

  /* Any read-only or read-write transaction implies a read-lock on 
  ** page 1. So if some other shared-cache client already has a write-lock 
  ** on page 1, the transaction cannot be opened. */
  rc = querySharedCacheTableLock(p, MASTER_ROOT, READ_LOCK);
  if( SQLITE_OK!=rc ) goto trans_begun;

  pBt->btsFlags &= ~BTS_INITIALLY_EMPTY;
  if( pBt->nPage==0 ) pBt->btsFlags |= BTS_INITIALLY_EMPTY;
  do {
    /* Call lockBtree() until either pBt->pPage1 is populated or
    ** lockBtree() returns something other than SQLITE_OK. lockBtree()
    ** may return SQLITE_OK but leave pBt->pPage1 set to 0 if after
    ** reading page 1 it discovers that the page-size of the database 
    ** file is not pBt->pageSize. In this case lockBtree() will update
    ** pBt->pageSize to the page-size of the file on disk.
    */
    while( pBt->pPage1==0 && SQLITE_OK==(rc = lockBtree(pBt)) );

    if( rc==SQLITE_OK && wrflag ){
      if( (pBt->btsFlags & BTS_READ_ONLY)!=0 ){
        rc = SQLITE_READONLY;
      }else{
        rc = sqlite3PagerBegin(pBt->pPager,wrflag>1,sqlite3TempInMemory(p->db));
        if( rc==SQLITE_OK ){
          rc = newDatabase(pBt);
        }else if( rc==SQLITE_BUSY_SNAPSHOT && pBt->inTransaction==TRANS_NONE ){
          /* if there was no transaction opened when this function was
          ** called and SQLITE_BUSY_SNAPSHOT is returned, change the error
          ** code to SQLITE_BUSY. */
          rc = SQLITE_BUSY;
        }
      }
    }
  
    if( rc!=SQLITE_OK ){
      unlockBtreeIfUnused(pBt);
    }
  }while( (rc&0xFF)==SQLITE_BUSY && pBt->inTransaction==TRANS_NONE &&
          btreeInvokeBusyHandler(pBt) );
  sqlite3PagerResetLockTimeout(pBt->pPager);

  if( rc==SQLITE_OK ){
    if( p->inTrans==TRANS_NONE ){
      pBt->nTransaction++;
#ifndef SQLITE_OMIT_SHARED_CACHE
      if( p->sharable ){
        assert( p->lock.pBtree==p && p->lock.iTable==1 );
        p->lock.eLock = READ_LOCK;
        p->lock.pNext = pBt->pLock;
        pBt->pLock = &p->lock;
      }
#endif
    }
    p->inTrans = (wrflag?TRANS_WRITE:TRANS_READ);
    if( p->inTrans>pBt->inTransaction ){
      pBt->inTransaction = p->inTrans;
    }
    if( wrflag ){
      MemPage *pPage1 = pBt->pPage1;
#ifndef SQLITE_OMIT_SHARED_CACHE
      assert( !pBt->pWriter );
      pBt->pWriter = p;
      pBt->btsFlags &= ~BTS_EXCLUSIVE;
      if( wrflag>1 ) pBt->btsFlags |= BTS_EXCLUSIVE;
#endif

      /* If the db-size header field is incorrect (as it may be if an old
      ** client has been writing the database file), update it now. Doing
      ** this sooner rather than later means the database size can safely 
      ** re-read the database size from page 1 if a savepoint or transaction
      ** rollback occurs within the transaction.
      */
      if( pBt->nPage!=get4byte(&pPage1->aData[28]) ){
        rc = sqlite3PagerWrite(pPage1->pDbPage);
        if( rc==SQLITE_OK ){
          put4byte(&pPage1->aData[28], pBt->nPage);
        }
      }
    }
  }

trans_begun:
  if( rc==SQLITE_OK ){
    if( pSchemaVersion ){
      *pSchemaVersion = get4byte(&pBt->pPage1->aData[40]);
    }
    if( wrflag ){
      /* This call makes sure that the pager has the correct number of
      ** open savepoints. If the second parameter is greater than 0 and
      ** the sub-journal is not already open, then it will be opened here.
      */
      rc = sqlite3PagerOpenSavepoint(pBt->pPager, p->db->nSavepoint);
    }
  }

  btreeIntegrity(p);
  sqlite3BtreeLeave(p);
  return rc;
}