#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  iRowid; scalar_t__ bEof; } ;
typedef  TYPE_1__ Fts5ExprNode ;
typedef  int /*<<< orphan*/  Fts5Expr ;

/* Variables and functions */
 int fts5RowidCmp (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int fts5NodeCompare(
  Fts5Expr *pExpr,
  Fts5ExprNode *p1, 
  Fts5ExprNode *p2
){
  if( p2->bEof ) return -1;
  if( p1->bEof ) return +1;
  return fts5RowidCmp(pExpr, p1->iRowid, p2->iRowid);
}