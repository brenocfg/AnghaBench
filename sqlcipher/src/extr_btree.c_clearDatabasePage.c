#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int /*<<< orphan*/  mutex; } ;
struct TYPE_12__ {int bBusy; int hdrOffset; int nCell; unsigned char* aData; int /*<<< orphan*/  pDbPage; scalar_t__ intKey; int /*<<< orphan*/  leaf; } ;
typedef  scalar_t__ Pgno ;
typedef  TYPE_1__ MemPage ;
typedef  int /*<<< orphan*/  CellInfo ;
typedef  TYPE_2__ BtShared ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int PTF_LEAF ; 
 int SQLITE_CORRUPT_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ btreePagecount (TYPE_2__*) ; 
 int clearCell (TYPE_1__*,unsigned char*,int /*<<< orphan*/ *) ; 
 unsigned char* findCell (TYPE_1__*,int) ; 
 int /*<<< orphan*/  freePage (TYPE_1__*,int*) ; 
 scalar_t__ get4byte (unsigned char*) ; 
 int getAndInitPage (TYPE_2__*,scalar_t__,TYPE_1__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  releasePage (TYPE_1__*) ; 
 int sqlite3PagerWrite (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 
 int /*<<< orphan*/  zeroPage (TYPE_1__*,int) ; 

__attribute__((used)) static int clearDatabasePage(
  BtShared *pBt,           /* The BTree that contains the table */
  Pgno pgno,               /* Page number to clear */
  int freePageFlag,        /* Deallocate page if true */
  int *pnChange            /* Add number of Cells freed to this counter */
){
  MemPage *pPage;
  int rc;
  unsigned char *pCell;
  int i;
  int hdr;
  CellInfo info;

  assert( sqlite3_mutex_held(pBt->mutex) );
  if( pgno>btreePagecount(pBt) ){
    return SQLITE_CORRUPT_BKPT;
  }
  rc = getAndInitPage(pBt, pgno, &pPage, 0, 0);
  if( rc ) return rc;
  if( pPage->bBusy ){
    rc = SQLITE_CORRUPT_BKPT;
    goto cleardatabasepage_out;
  }
  pPage->bBusy = 1;
  hdr = pPage->hdrOffset;
  for(i=0; i<pPage->nCell; i++){
    pCell = findCell(pPage, i);
    if( !pPage->leaf ){
      rc = clearDatabasePage(pBt, get4byte(pCell), 1, pnChange);
      if( rc ) goto cleardatabasepage_out;
    }
    rc = clearCell(pPage, pCell, &info);
    if( rc ) goto cleardatabasepage_out;
  }
  if( !pPage->leaf ){
    rc = clearDatabasePage(pBt, get4byte(&pPage->aData[hdr+8]), 1, pnChange);
    if( rc ) goto cleardatabasepage_out;
  }else if( pnChange ){
    assert( pPage->intKey || CORRUPT_DB );
    testcase( !pPage->intKey );
    *pnChange += pPage->nCell;
  }
  if( freePageFlag ){
    freePage(pPage, &rc);
  }else if( (rc = sqlite3PagerWrite(pPage->pDbPage))==0 ){
    zeroPage(pPage, pPage->aData[hdr] | PTF_LEAF);
  }

cleardatabasepage_out:
  pPage->bBusy = 0;
  releasePage(pPage);
  return rc;
}