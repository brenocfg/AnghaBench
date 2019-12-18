#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  pFuncArg; int /*<<< orphan*/  zIndexedBy; } ;
struct TYPE_6__ {scalar_t__ isTabFunc; scalar_t__ isIndexedBy; } ;
struct SrcList_item {int /*<<< orphan*/  pUsing; int /*<<< orphan*/  pOn; int /*<<< orphan*/  pSelect; int /*<<< orphan*/  pTab; TYPE_2__ u1; TYPE_1__ fg; int /*<<< orphan*/  zAlias; int /*<<< orphan*/  zName; int /*<<< orphan*/  zDatabase; } ;
typedef  int /*<<< orphan*/  sqlite3 ;
struct TYPE_8__ {int nSrc; struct SrcList_item* a; } ;
typedef  TYPE_3__ SrcList ;

/* Variables and functions */
 int /*<<< orphan*/  sqlite3DbFree (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3DbFreeNN (int /*<<< orphan*/ *,TYPE_3__*) ; 
 int /*<<< orphan*/  sqlite3DeleteTable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3IdListDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sqlite3SelectDelete (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void sqlite3SrcListDelete(sqlite3 *db, SrcList *pList){
  int i;
  struct SrcList_item *pItem;
  if( pList==0 ) return;
  for(pItem=pList->a, i=0; i<pList->nSrc; i++, pItem++){
    sqlite3DbFree(db, pItem->zDatabase);
    sqlite3DbFree(db, pItem->zName);
    sqlite3DbFree(db, pItem->zAlias);
    if( pItem->fg.isIndexedBy ) sqlite3DbFree(db, pItem->u1.zIndexedBy);
    if( pItem->fg.isTabFunc ) sqlite3ExprListDelete(db, pItem->u1.pFuncArg);
    sqlite3DeleteTable(db, pItem->pTab);
    sqlite3SelectDelete(db, pItem->pSelect);
    sqlite3ExprDelete(db, pItem->pOn);
    sqlite3IdListDelete(db, pItem->pUsing);
  }
  sqlite3DbFreeNN(db, pList);
}