#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {TYPE_4__* pSelect; } ;
struct TYPE_14__ {TYPE_3__ u; } ;
typedef  TYPE_5__ Walker ;
struct TYPE_10__ {TYPE_2__* pWin; } ;
struct TYPE_15__ {scalar_t__ op; TYPE_1__ y; } ;
struct TYPE_13__ {TYPE_2__* pWin; } ;
struct TYPE_11__ {struct TYPE_11__* pNextWin; } ;
typedef  TYPE_6__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  EP_WinFunc ; 
 int /*<<< orphan*/  ExprHasProperty (TYPE_6__*,int /*<<< orphan*/ ) ; 
 scalar_t__ TK_FUNCTION ; 
 int WRC_Continue ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int gatherSelectWindowsCallback(Walker *pWalker, Expr *pExpr){
  if( pExpr->op==TK_FUNCTION && pExpr->y.pWin!=0 ){
    assert( ExprHasProperty(pExpr, EP_WinFunc) );
    pExpr->y.pWin->pNextWin = pWalker->u.pSelect->pWin;
    pWalker->u.pSelect->pWin = pExpr->y.pWin;
  }
  return WRC_Continue;
}