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
typedef  scalar_t__ u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_7__ {int nCell; int hdrOffset; scalar_t__ nFree; scalar_t__ childPtrSize; TYPE_1__* pBt; scalar_t__* aCellIdx; scalar_t__* aData; int /*<<< orphan*/  pDbPage; } ;
struct TYPE_6__ {scalar_t__ usableSize; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;

/* Variables and functions */
 scalar_t__ CORRUPT_DB ; 
 int SQLITE_CORRUPT_BKPT ; 
 int /*<<< orphan*/  assert (int) ; 
 int cellSize (TYPE_2__*,int) ; 
 int freeSpace (TYPE_2__*,scalar_t__,int) ; 
 scalar_t__ get2byte (scalar_t__*) ; 
 int /*<<< orphan*/  memmove (scalar_t__*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (scalar_t__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put2byte (scalar_t__*,int) ; 
 int sqlite3PagerIswriteable (int /*<<< orphan*/ ) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void dropCell(MemPage *pPage, int idx, int sz, int *pRC){
  u32 pc;         /* Offset to cell content of cell being deleted */
  u8 *data;       /* pPage->aData */
  u8 *ptr;        /* Used to move bytes around within data[] */
  int rc;         /* The return code */
  int hdr;        /* Beginning of the header.  0 most pages.  100 page 1 */

  if( *pRC ) return;
  assert( idx>=0 && idx<pPage->nCell );
  assert( CORRUPT_DB || sz==cellSize(pPage, idx) );
  assert( sqlite3PagerIswriteable(pPage->pDbPage) );
  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  data = pPage->aData;
  ptr = &pPage->aCellIdx[2*idx];
  pc = get2byte(ptr);
  hdr = pPage->hdrOffset;
  testcase( pc==get2byte(&data[hdr+5]) );
  testcase( pc+sz==pPage->pBt->usableSize );
  if( pc+sz > pPage->pBt->usableSize ){
    *pRC = SQLITE_CORRUPT_BKPT;
    return;
  }
  rc = freeSpace(pPage, pc, sz);
  if( rc ){
    *pRC = rc;
    return;
  }
  pPage->nCell--;
  if( pPage->nCell==0 ){
    memset(&data[hdr+1], 0, 4);
    data[hdr+7] = 0;
    put2byte(&data[hdr+5], pPage->pBt->usableSize);
    pPage->nFree = pPage->pBt->usableSize - pPage->hdrOffset
                       - pPage->childPtrSize - 8;
  }else{
    memmove(ptr, ptr+2, 2*(pPage->nCell - idx));
    put2byte(&data[hdr+3], pPage->nCell);
    pPage->nFree += 2;
  }
}