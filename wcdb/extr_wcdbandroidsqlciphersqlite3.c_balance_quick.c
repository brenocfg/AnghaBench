#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  int u16 ;
struct TYPE_20__ {int usableSize; int /*<<< orphan*/  mutex; } ;
struct TYPE_19__ {int nCell; int* szCell; int* ixNx; int /*<<< orphan*/ * apEnd; int /*<<< orphan*/ ** apCell; TYPE_1__* pRef; } ;
struct TYPE_18__ {int nOverflow; scalar_t__ nCell; int (* xCellSize ) (TYPE_1__*,int /*<<< orphan*/ *) ;int* aData; int nFree; int cellOffset; int minLocal; int hdrOffset; int /*<<< orphan*/  pgno; int /*<<< orphan*/  aDataEnd; int /*<<< orphan*/  pDbPage; int /*<<< orphan*/ ** apOvfl; TYPE_3__* pBt; } ;
typedef  int /*<<< orphan*/  Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  TYPE_2__ CellArray ;
typedef  TYPE_3__ BtShared ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 scalar_t__ ISAUTOVACUUM ; 
 scalar_t__ NEVER (int) ; 
 int PTF_INTKEY ; 
 int PTF_LEAF ; 
 int PTF_LEAFDATA ; 
 int /*<<< orphan*/  PTRMAP_BTREE ; 
 int SQLITE_CORRUPT_BKPT ; 
 int SQLITE_OK ; 
 int allocateBtreePage (TYPE_3__* const,TYPE_1__**,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/ * findCell (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  insertCell (TYPE_1__*,scalar_t__,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ptrmapPut (TYPE_3__* const,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  ptrmapPutOvflPtr (TYPE_1__*,TYPE_1__*,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  put4byte (int*,int /*<<< orphan*/ ) ; 
 int rebuildPage (TYPE_2__*,int /*<<< orphan*/ ,int,TYPE_1__*) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zeroPage (TYPE_1__*,int) ; 

__attribute__((used)) static int balance_quick(MemPage *pParent, MemPage *pPage, u8 *pSpace){
  BtShared *const pBt = pPage->pBt;    /* B-Tree Database */
  MemPage *pNew;                       /* Newly allocated page */
  int rc;                              /* Return Code */
  Pgno pgnoNew;                        /* Page number of pNew */

  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( sqlite3PagerIswriteable(pParent->pDbPage) );
  assert( pPage->nOverflow==1 );

  if( pPage->nCell==0 ) return SQLITE_CORRUPT_BKPT;  /* dbfuzz001.test */

  /* Allocate a new page. This page will become the right-sibling of 
  ** pPage. Make the parent page writable, so that the new divider cell
  ** may be inserted. If both these operations are successful, proceed.
  */
  rc = allocateBtreePage(pBt, &pNew, &pgnoNew, 0, 0);

  if( rc==SQLITE_OK ){

    u8 *pOut = &pSpace[4];
    u8 *pCell = pPage->apOvfl[0];
    u16 szCell = pPage->xCellSize(pPage, pCell);
    u8 *pStop;
    CellArray b;

    assert( sqlite3PagerIswriteable(pNew->pDbPage) );
    assert( CORRUPT_DB || pPage->aData[0]==(PTF_INTKEY|PTF_LEAFDATA|PTF_LEAF) );
    zeroPage(pNew, PTF_INTKEY|PTF_LEAFDATA|PTF_LEAF);
    b.nCell = 1;
    b.pRef = pPage;
    b.apCell = &pCell;
    b.szCell = &szCell;
    b.apEnd[0] = pPage->aDataEnd;
    b.ixNx[0] = 2;
    rc = rebuildPage(&b, 0, 1, pNew);
    if( NEVER(rc) ){
      releasePage(pNew);
      return rc;
    }
    pNew->nFree = pBt->usableSize - pNew->cellOffset - 2 - szCell;

    /* If this is an auto-vacuum database, update the pointer map
    ** with entries for the new page, and any pointer from the 
    ** cell on the page to an overflow page. If either of these
    ** operations fails, the return code is set, but the contents
    ** of the parent page are still manipulated by thh code below.
    ** That is Ok, at this point the parent page is guaranteed to
    ** be marked as dirty. Returning an error code will cause a
    ** rollback, undoing any changes made to the parent page.
    */
    if( ISAUTOVACUUM ){
      ptrmapPut(pBt, pgnoNew, PTRMAP_BTREE, pParent->pgno, &rc);
      if( szCell>pNew->minLocal ){
        ptrmapPutOvflPtr(pNew, pNew, pCell, &rc);
      }
    }
  
    /* Create a divider cell to insert into pParent. The divider cell
    ** consists of a 4-byte page number (the page number of pPage) and
    ** a variable length key value (which must be the same value as the
    ** largest key on pPage).
    **
    ** To find the largest key value on pPage, first find the right-most 
    ** cell on pPage. The first two fields of this cell are the 
    ** record-length (a variable length integer at most 32-bits in size)
    ** and the key value (a variable length integer, may have any value).
    ** The first of the while(...) loops below skips over the record-length
    ** field. The second while(...) loop copies the key value from the
    ** cell on pPage into the pSpace buffer.
    */
    pCell = findCell(pPage, pPage->nCell-1);
    pStop = &pCell[9];
    while( (*(pCell++)&0x80) && pCell<pStop );
    pStop = &pCell[9];
    while( ((*(pOut++) = *(pCell++))&0x80) && pCell<pStop );

    /* Insert the new divider cell into pParent. */
    if( rc==SQLITE_OK ){
      insertCell(pParent, pParent->nCell, pSpace, (int)(pOut-pSpace),
                   0, pPage->pgno, &rc);
    }

    /* Set the right-child pointer of pParent to point to the new page. */
    put4byte(&pParent->aData[pParent->hdrOffset+8], pgnoNew);
  
    /* Release the reference to the new page. */
    releasePage(pNew);
  }

  return rc;
}