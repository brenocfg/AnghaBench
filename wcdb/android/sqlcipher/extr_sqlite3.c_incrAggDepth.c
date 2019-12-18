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
struct TYPE_6__ {scalar_t__ n; } ;
struct TYPE_7__ {TYPE_1__ u; } ;
typedef  TYPE_2__ Walker ;
struct TYPE_8__ {scalar_t__ op; int /*<<< orphan*/  op2; } ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 scalar_t__ TK_AGG_FUNCTION ; 
 int WRC_Continue ; 

__attribute__((used)) static int incrAggDepth(Walker *pWalker, Expr *pExpr){
  if( pExpr->op==TK_AGG_FUNCTION ) pExpr->op2 += pWalker->u.n;
  return WRC_Continue;
}