#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {int /*<<< orphan*/  pFuncArg; void* zIndexedBy; } ;
struct TYPE_8__ {scalar_t__ isTabFunc; scalar_t__ isIndexedBy; } ;
struct SrcList_item {int /*<<< orphan*/  colUsed; int /*<<< orphan*/  pUsing; int /*<<< orphan*/  pOn; int /*<<< orphan*/  pSelect; TYPE_3__* pTab; TYPE_2__ u1; TYPE_1__ fg; int /*<<< orphan*/  pIBIndex; int /*<<< orphan*/  regReturn; int /*<<< orphan*/  addrFillSub; int /*<<< orphan*/  iCursor; void* zAlias; void* zName; void* zDatabase; int /*<<< orphan*/  pSchema; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_10__ {int /*<<< orphan*/  nTabRef; } ;
typedef  TYPE_3__ Table ;
struct TYPE_11__ {int nSrc; int nAlloc; struct SrcList_item* a; } ;
typedef  TYPE_4__ SrcList ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* sqlite3DbMallocRawNN (int /*<<< orphan*/ *,int) ; 
 void* sqlite3DbStrDup (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  sqlite3ExprDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ExprListDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3IdListDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SelectDup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

SrcList *sqlite3SrcListDup(sqlite3 *db, SrcList *p, int flags){
  SrcList *pNew;
  int i;
  int nByte;
  assert( db!=0 );
  if( p==0 ) return 0;
  nByte = sizeof(*p) + (p->nSrc>0 ? sizeof(p->a[0]) * (p->nSrc-1) : 0);
  pNew = sqlite3DbMallocRawNN(db, nByte );
  if( pNew==0 ) return 0;
  pNew->nSrc = pNew->nAlloc = p->nSrc;
  for(i=0; i<p->nSrc; i++){
    struct SrcList_item *pNewItem = &pNew->a[i];
    struct SrcList_item *pOldItem = &p->a[i];
    Table *pTab;
    pNewItem->pSchema = pOldItem->pSchema;
    pNewItem->zDatabase = sqlite3DbStrDup(db, pOldItem->zDatabase);
    pNewItem->zName = sqlite3DbStrDup(db, pOldItem->zName);
    pNewItem->zAlias = sqlite3DbStrDup(db, pOldItem->zAlias);
    pNewItem->fg = pOldItem->fg;
    pNewItem->iCursor = pOldItem->iCursor;
    pNewItem->addrFillSub = pOldItem->addrFillSub;
    pNewItem->regReturn = pOldItem->regReturn;
    if( pNewItem->fg.isIndexedBy ){
      pNewItem->u1.zIndexedBy = sqlite3DbStrDup(db, pOldItem->u1.zIndexedBy);
    }
    pNewItem->pIBIndex = pOldItem->pIBIndex;
    if( pNewItem->fg.isTabFunc ){
      pNewItem->u1.pFuncArg = 
          sqlite3ExprListDup(db, pOldItem->u1.pFuncArg, flags);
    }
    pTab = pNewItem->pTab = pOldItem->pTab;
    if( pTab ){
      pTab->nTabRef++;
    }
    pNewItem->pSelect = sqlite3SelectDup(db, pOldItem->pSelect, flags);
    pNewItem->pOn = sqlite3ExprDup(db, pOldItem->pOn, flags);
    pNewItem->pUsing = sqlite3IdListDup(db, pOldItem->pUsing);
    pNewItem->colUsed = pOldItem->colUsed;
  }
  return pNew;
}