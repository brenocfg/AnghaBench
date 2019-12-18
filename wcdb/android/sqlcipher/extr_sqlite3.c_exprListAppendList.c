#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_13__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_12__ {int /*<<< orphan*/  db; } ;
struct TYPE_11__ {int /*<<< orphan*/  sortOrder; int /*<<< orphan*/  pExpr; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ ExprList ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/ * sqlite3ExprDup (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* sqlite3ExprListAppend (TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ExprList *exprListAppendList(
  Parse *pParse,          /* Parsing context */
  ExprList *pList,        /* List to which to append. Might be NULL */
  ExprList *pAppend       /* List of values to append. Might be NULL */
){
  if( pAppend ){
    int i;
    int nInit = pList ? pList->nExpr : 0;
    for(i=0; i<pAppend->nExpr; i++){
      Expr *pDup = sqlite3ExprDup(pParse->db, pAppend->a[i].pExpr, 0);
      pList = sqlite3ExprListAppend(pParse, pList, pDup);
      if( pList ) pList->a[nInit+i].sortOrder = pAppend->a[i].sortOrder;
    }
  }
  return pList;
}