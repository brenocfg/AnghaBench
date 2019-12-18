#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {scalar_t__ n; } ;
typedef  TYPE_1__ Token ;
struct TYPE_12__ {int flags; struct TYPE_12__* pLeft; } ;
struct TYPE_11__ {int /*<<< orphan*/  db; } ;
typedef  TYPE_2__ Parse ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int EP_Collate ; 
 int EP_Skip ; 
 int /*<<< orphan*/  TK_COLLATE ; 
 TYPE_3__* sqlite3ExprAlloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__ const*,int) ; 

Expr *sqlite3ExprAddCollateToken(
  Parse *pParse,           /* Parsing context */
  Expr *pExpr,             /* Add the "COLLATE" clause to this expression */
  const Token *pCollName,  /* Name of collating sequence */
  int dequote              /* True to dequote pCollName */
){
  if( pCollName->n>0 ){
    Expr *pNew = sqlite3ExprAlloc(pParse->db, TK_COLLATE, pCollName, dequote);
    if( pNew ){
      pNew->pLeft = pExpr;
      pNew->flags |= EP_Collate|EP_Skip;
      pExpr = pNew;
    }
  }
  return pExpr;
}