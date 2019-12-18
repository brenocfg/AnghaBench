#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ notIndexed; scalar_t__ isIndexedBy; int isTabFunc; } ;
struct TYPE_7__ {int /*<<< orphan*/ * pFuncArg; } ;
struct SrcList_item {TYPE_2__ fg; TYPE_1__ u1; } ;
struct TYPE_10__ {int /*<<< orphan*/  db; } ;
struct TYPE_9__ {int nSrc; struct SrcList_item* a; } ;
typedef  TYPE_3__ SrcList ;
typedef  TYPE_4__ Parse ;
typedef  int /*<<< orphan*/  ExprList ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  sqlite3ExprListDelete (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

void sqlite3SrcListFuncArgs(Parse *pParse, SrcList *p, ExprList *pList){
  if( p ){
    struct SrcList_item *pItem = &p->a[p->nSrc-1];
    assert( pItem->fg.notIndexed==0 );
    assert( pItem->fg.isIndexedBy==0 );
    assert( pItem->fg.isTabFunc==0 );
    pItem->u1.pFuncArg = pList;
    pItem->fg.isTabFunc = 1;
  }else{
    sqlite3ExprListDelete(pParse->db, pList);
  }
}