#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u8 ;
struct TYPE_10__ {TYPE_3__* pSelect; TYPE_1__* pList; } ;
struct TYPE_11__ {scalar_t__ op; scalar_t__ op2; TYPE_4__ x; } ;
struct TYPE_9__ {TYPE_2__* pEList; } ;
struct TYPE_8__ {int nExpr; } ;
struct TYPE_7__ {int nExpr; } ;
typedef  TYPE_5__ Expr ;

/* Variables and functions */
 scalar_t__ TK_REGISTER ; 
 scalar_t__ TK_SELECT ; 
 scalar_t__ TK_VECTOR ; 

int sqlite3ExprVectorSize(Expr *pExpr){
  u8 op = pExpr->op;
  if( op==TK_REGISTER ) op = pExpr->op2;
  if( op==TK_VECTOR ){
    return pExpr->x.pList->nExpr;
  }else if( op==TK_SELECT ){
    return pExpr->x.pSelect->pEList->nExpr;
  }else{
    return 1;
  }
}