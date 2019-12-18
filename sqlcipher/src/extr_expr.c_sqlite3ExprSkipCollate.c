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
struct TYPE_10__ {TYPE_2__* pList; } ;
struct TYPE_11__ {scalar_t__ op; struct TYPE_11__* pLeft; TYPE_3__ x; } ;
struct TYPE_9__ {scalar_t__ nExpr; TYPE_1__* a; } ;
struct TYPE_8__ {TYPE_4__* pExpr; } ;
typedef  TYPE_4__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_Skip ; 
 int /*<<< orphan*/  EP_Unlikely ; 
 int /*<<< orphan*/  EP_xIsSelect ; 
 scalar_t__ ExprHasProperty (TYPE_4__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_COLLATE ; 
 scalar_t__ TK_FUNCTION ; 
 int /*<<< orphan*/  assert (int) ; 

Expr *sqlite3ExprSkipCollate(Expr *pExpr){
  while( pExpr && ExprHasProperty(pExpr, EP_Skip) ){
    if( ExprHasProperty(pExpr, EP_Unlikely) ){
      assert( !ExprHasProperty(pExpr, EP_xIsSelect) );
      assert( pExpr->x.pList->nExpr>0 );
      assert( pExpr->op==TK_FUNCTION );
      pExpr = pExpr->x.pList->a[0].pExpr;
    }else{
      assert( pExpr->op==TK_COLLATE );
      pExpr = pExpr->pLeft;
    }
  }   
  return pExpr;
}