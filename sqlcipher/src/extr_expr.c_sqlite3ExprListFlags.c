#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_7__ {int /*<<< orphan*/  flags; } ;
struct TYPE_6__ {int nExpr; TYPE_1__* a; } ;
struct TYPE_5__ {TYPE_3__* pExpr; } ;
typedef  TYPE_2__ ExprList ;
typedef  TYPE_3__ Expr ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

u32 sqlite3ExprListFlags(const ExprList *pList){
  int i;
  u32 m = 0;
  assert( pList!=0 );
  for(i=0; i<pList->nExpr; i++){
     Expr *pExpr = pList->a[i].pExpr;
     assert( pExpr!=0 );
     m |= pExpr->flags;
  }
  return m;
}