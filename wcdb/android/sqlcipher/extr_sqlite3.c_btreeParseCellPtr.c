#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int u8 ;
typedef  int u64 ;
typedef  int u32 ;
typedef  void* u16 ;
typedef  int /*<<< orphan*/  i64 ;
struct TYPE_10__ {int nPayload; int* pPayload; int nSize; void* nLocal; int /*<<< orphan*/  nKey; } ;
struct TYPE_9__ {int leaf; int intKeyLeaf; scalar_t__ childPtrSize; int maxLocal; TYPE_1__* pBt; } ;
struct TYPE_8__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ MemPage ;
typedef  TYPE_3__ CellInfo ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  btreeParseCellAdjustSizeForOverflow (TYPE_2__*,int*,TYPE_3__*) ; 
 int sqlite3_mutex_held (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  testcase (int) ; 

__attribute__((used)) static void btreeParseCellPtr(
  MemPage *pPage,         /* Page containing the cell */
  u8 *pCell,              /* Pointer to the cell text. */
  CellInfo *pInfo         /* Fill in this structure */
){
  u8 *pIter;              /* For scanning through pCell */
  u32 nPayload;           /* Number of bytes of cell payload */
  u64 iKey;               /* Extracted Key value */

  assert( sqlite3_mutex_held(pPage->pBt->mutex) );
  assert( pPage->leaf==0 || pPage->leaf==1 );
  assert( pPage->intKeyLeaf );
  assert( pPage->childPtrSize==0 );
  pIter = pCell;

  /* The next block of code is equivalent to:
  **
  **     pIter += getVarint32(pIter, nPayload);
  **
  ** The code is inlined to avoid a function call.
  */
  nPayload = *pIter;
  if( nPayload>=0x80 ){
    u8 *pEnd = &pIter[8];
    nPayload &= 0x7f;
    do{
      nPayload = (nPayload<<7) | (*++pIter & 0x7f);
    }while( (*pIter)>=0x80 && pIter<pEnd );
  }
  pIter++;

  /* The next block of code is equivalent to:
  **
  **     pIter += getVarint(pIter, (u64*)&pInfo->nKey);
  **
  ** The code is inlined to avoid a function call.
  */
  iKey = *pIter;
  if( iKey>=0x80 ){
    u8 *pEnd = &pIter[7];
    iKey &= 0x7f;
    while(1){
      iKey = (iKey<<7) | (*++pIter & 0x7f);
      if( (*pIter)<0x80 ) break;
      if( pIter>=pEnd ){
        iKey = (iKey<<8) | *++pIter;
        break;
      }
    }
  }
  pIter++;

  pInfo->nKey = *(i64*)&iKey;
  pInfo->nPayload = nPayload;
  pInfo->pPayload = pIter;
  testcase( nPayload==pPage->maxLocal );
  testcase( nPayload==pPage->maxLocal+1 );
  if( nPayload<=pPage->maxLocal ){
    /* This is the (easy) common case where the entire payload fits
    ** on the local page.  No overflow is required.
    */
    pInfo->nSize = nPayload + (u16)(pIter - pCell);
    if( pInfo->nSize<4 ) pInfo->nSize = 4;
    pInfo->nLocal = (u16)nPayload;
  }else{
    btreeParseCellAdjustSizeForOverflow(pPage, pCell, pInfo);
  }
}