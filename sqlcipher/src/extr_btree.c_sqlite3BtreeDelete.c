#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
struct TYPE_31__ {int /*<<< orphan*/  nKey; } ;
struct TYPE_36__ {int curFlags; scalar_t__ pKeyInfo; scalar_t__ eState; int iPage; int ix; int skipNext; TYPE_2__* pPage; TYPE_2__** apPage; TYPE_1__ info; int /*<<< orphan*/  pgnoRoot; TYPE_4__* pBtree; } ;
struct TYPE_35__ {scalar_t__ inTransaction; int btsFlags; int usableSize; unsigned char* pTmpSpace; } ;
struct TYPE_34__ {TYPE_5__* pBt; } ;
struct TYPE_33__ {int nSize; } ;
struct TYPE_32__ {int nFree; int nCell; unsigned char* aData; int (* xCellSize ) (TYPE_2__*,unsigned char*) ;int /*<<< orphan*/  pDbPage; int /*<<< orphan*/  pgno; int /*<<< orphan*/  leaf; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ CellInfo ;
typedef  TYPE_4__ Btree ;
typedef  TYPE_5__ BtShared ;
typedef  TYPE_6__ BtCursor ;

/* Variables and functions */
 int BTCF_Multiple ; 
 int BTCF_WriteFlag ; 
 int BTREE_AUXDELETE ; 
 int BTREE_SAVEPOSITION ; 
 int BTS_READ_ONLY ; 
 scalar_t__ CORRUPT_DB ; 
 scalar_t__ CURSOR_REQUIRESEEK ; 
 scalar_t__ CURSOR_SKIPNEXT ; 
 scalar_t__ CURSOR_VALID ; 
 int MX_CELL_SIZE (TYPE_5__*) ; 
 int SQLITE_CORRUPT ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_DONE ; 
 int SQLITE_EMPTY ; 
 int SQLITE_OK ; 
 scalar_t__ TRANS_WRITE ; 
 int /*<<< orphan*/  assert (int) ; 
 int balance (TYPE_6__*) ; 
 int btreeComputeFreeSpace (TYPE_2__*) ; 
 int /*<<< orphan*/  btreeReleaseAllCursorPages (TYPE_6__*) ; 
 int btreeRestoreCursorPosition (TYPE_6__*) ; 
 int cellSizePtr (TYPE_2__*,unsigned char*) ; 
 int clearCell (TYPE_2__*,unsigned char*,TYPE_3__*) ; 
 int cursorOwnsBtShared (TYPE_6__*) ; 
 int /*<<< orphan*/  dropCell (TYPE_2__*,int,int,int*) ; 
 unsigned char* findCell (TYPE_2__*,int) ; 
 int /*<<< orphan*/  hasReadConflicts (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int hasSharedCacheTableLock (TYPE_4__*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  insertCell (TYPE_2__*,int,unsigned char*,int,unsigned char*,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  invalidateIncrblobCursors (TYPE_4__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int moveToRoot (TYPE_6__*) ; 
 int /*<<< orphan*/  releasePage (TYPE_2__*) ; 
 int /*<<< orphan*/  releasePageNotNull (TYPE_2__*) ; 
 int saveAllCursors (TYPE_5__*,int /*<<< orphan*/ ,TYPE_6__*) ; 
 int saveCursorKey (TYPE_6__*) ; 
 int sqlite3BtreePrevious (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_2__*,unsigned char*) ; 

int sqlite3BtreeDelete(BtCursor *pCur, u8 flags){
  Btree *p = pCur->pBtree;
  BtShared *pBt = p->pBt;              
  int rc;                              /* Return code */
  MemPage *pPage;                      /* Page to delete cell from */
  unsigned char *pCell;                /* Pointer to cell to delete */
  int iCellIdx;                        /* Index of cell to delete */
  int iCellDepth;                      /* Depth of node containing pCell */ 
  CellInfo info;                       /* Size of the cell being deleted */
  int bSkipnext = 0;                   /* Leaf cursor in SKIPNEXT state */
  u8 bPreserve = flags & BTREE_SAVEPOSITION;  /* Keep cursor valid */

  assert( cursorOwnsBtShared(pCur) );
  assert( pBt->inTransaction==TRANS_WRITE );
  assert( (pBt->btsFlags & BTS_READ_ONLY)==0 );
  assert( pCur->curFlags & BTCF_WriteFlag );
  assert( hasSharedCacheTableLock(p, pCur->pgnoRoot, pCur->pKeyInfo!=0, 2) );
  assert( !hasReadConflicts(p, pCur->pgnoRoot) );
  assert( (flags & ~(BTREE_SAVEPOSITION | BTREE_AUXDELETE))==0 );
  if( pCur->eState==CURSOR_REQUIRESEEK ){
    rc = btreeRestoreCursorPosition(pCur);
    if( rc ) return rc;
  }
  assert( pCur->eState==CURSOR_VALID );

  iCellDepth = pCur->iPage;
  iCellIdx = pCur->ix;
  pPage = pCur->pPage;
  pCell = findCell(pPage, iCellIdx);
  if( pPage->nFree<0 && btreeComputeFreeSpace(pPage) ) return SQLITE_CORRUPT;

  /* If the bPreserve flag is set to true, then the cursor position must
  ** be preserved following this delete operation. If the current delete
  ** will cause a b-tree rebalance, then this is done by saving the cursor
  ** key and leaving the cursor in CURSOR_REQUIRESEEK state before 
  ** returning. 
  **
  ** Or, if the current delete will not cause a rebalance, then the cursor
  ** will be left in CURSOR_SKIPNEXT state pointing to the entry immediately
  ** before or after the deleted entry. In this case set bSkipnext to true.  */
  if( bPreserve ){
    if( !pPage->leaf 
     || (pPage->nFree+cellSizePtr(pPage,pCell)+2)>(int)(pBt->usableSize*2/3)
     || pPage->nCell==1  /* See dbfuzz001.test for a test case */
    ){
      /* A b-tree rebalance will be required after deleting this entry.
      ** Save the cursor key.  */
      rc = saveCursorKey(pCur);
      if( rc ) return rc;
    }else{
      bSkipnext = 1;
    }
  }

  /* If the page containing the entry to delete is not a leaf page, move
  ** the cursor to the largest entry in the tree that is smaller than
  ** the entry being deleted. This cell will replace the cell being deleted
  ** from the internal node. The 'previous' entry is used for this instead
  ** of the 'next' entry, as the previous entry is always a part of the
  ** sub-tree headed by the child page of the cell being deleted. This makes
  ** balancing the tree following the delete operation easier.  */
  if( !pPage->leaf ){
    rc = sqlite3BtreePrevious(pCur, 0);
    assert( rc!=SQLITE_DONE );
    if( rc ) return rc;
  }

  /* Save the positions of any other cursors open on this table before
  ** making any modifications.  */
  if( pCur->curFlags & BTCF_Multiple ){
    rc = saveAllCursors(pBt, pCur->pgnoRoot, pCur);
    if( rc ) return rc;
  }

  /* If this is a delete operation to remove a row from a table b-tree,
  ** invalidate any incrblob cursors open on the row being deleted.  */
  if( pCur->pKeyInfo==0 ){
    invalidateIncrblobCursors(p, pCur->pgnoRoot, pCur->info.nKey, 0);
  }

  /* Make the page containing the entry to be deleted writable. Then free any
  ** overflow pages associated with the entry and finally remove the cell
  ** itself from within the page.  */
  rc = sqlite3PagerWrite(pPage->pDbPage);
  if( rc ) return rc;
  rc = clearCell(pPage, pCell, &info);
  dropCell(pPage, iCellIdx, info.nSize, &rc);
  if( rc ) return rc;

  /* If the cell deleted was not located on a leaf page, then the cursor
  ** is currently pointing to the largest entry in the sub-tree headed
  ** by the child-page of the cell that was just deleted from an internal
  ** node. The cell from the leaf node needs to be moved to the internal
  ** node to replace the deleted cell.  */
  if( !pPage->leaf ){
    MemPage *pLeaf = pCur->pPage;
    int nCell;
    Pgno n;
    unsigned char *pTmp;

    if( pLeaf->nFree<0 ){
      rc = btreeComputeFreeSpace(pLeaf);
      if( rc ) return rc;
    }
    if( iCellDepth<pCur->iPage-1 ){
      n = pCur->apPage[iCellDepth+1]->pgno;
    }else{
      n = pCur->pPage->pgno;
    }
    pCell = findCell(pLeaf, pLeaf->nCell-1);
    if( pCell<&pLeaf->aData[4] ) return SQLITE_CORRUPT_BKPT;
    nCell = pLeaf->xCellSize(pLeaf, pCell);
    assert( MX_CELL_SIZE(pBt) >= nCell );
    pTmp = pBt->pTmpSpace;
    assert( pTmp!=0 );
    rc = sqlite3PagerWrite(pLeaf->pDbPage);
    if( rc==SQLITE_OK ){
      insertCell(pPage, iCellIdx, pCell-4, nCell+4, pTmp, n, &rc);
    }
    dropCell(pLeaf, pLeaf->nCell-1, nCell, &rc);
    if( rc ) return rc;
  }

  /* Balance the tree. If the entry deleted was located on a leaf page,
  ** then the cursor still points to that page. In this case the first
  ** call to balance() repairs the tree, and the if(...) condition is
  ** never true.
  **
  ** Otherwise, if the entry deleted was on an internal node page, then
  ** pCur is pointing to the leaf page from which a cell was removed to
  ** replace the cell deleted from the internal node. This is slightly
  ** tricky as the leaf node may be underfull, and the internal node may
  ** be either under or overfull. In this case run the balancing algorithm
  ** on the leaf node first. If the balance proceeds far enough up the
  ** tree that we can be sure that any problem in the internal node has
  ** been corrected, so be it. Otherwise, after balancing the leaf node,
  ** walk the cursor up the tree to the internal node and balance it as 
  ** well.  */
  rc = balance(pCur);
  if( rc==SQLITE_OK && pCur->iPage>iCellDepth ){
    releasePageNotNull(pCur->pPage);
    pCur->iPage--;
    while( pCur->iPage>iCellDepth ){
      releasePage(pCur->apPage[pCur->iPage--]);
    }
    pCur->pPage = pCur->apPage[pCur->iPage];
    rc = balance(pCur);
  }

  if( rc==SQLITE_OK ){
    if( bSkipnext ){
      assert( bPreserve && (pCur->iPage==iCellDepth || CORRUPT_DB) );
      assert( pPage==pCur->pPage || CORRUPT_DB );
      assert( (pPage->nCell>0 || CORRUPT_DB) && iCellIdx<=pPage->nCell );
      pCur->eState = CURSOR_SKIPNEXT;
      if( iCellIdx>=pPage->nCell ){
        pCur->skipNext = -1;
        pCur->ix = pPage->nCell-1;
      }else{
        pCur->skipNext = 1;
      }
    }else{
      rc = moveToRoot(pCur);
      if( bPreserve ){
        btreeReleaseAllCursorPages(pCur);
        pCur->eState = CURSOR_REQUIRESEEK;
      }
      if( rc==SQLITE_EMPTY ) rc = SQLITE_OK;
    }
  }
  return rc;
}