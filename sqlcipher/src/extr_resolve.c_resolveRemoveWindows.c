#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * pSelect; } ;
struct TYPE_6__ {TYPE_1__ u; int /*<<< orphan*/  xExprCallback; } ;
typedef  TYPE_2__ Walker ;
typedef  int /*<<< orphan*/  Select ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  resolveRemoveWindowsCb ; 
 int /*<<< orphan*/  sqlite3WalkExpr (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void resolveRemoveWindows(Select *pSelect, Expr *pExpr){
  Walker sWalker;
  memset(&sWalker, 0, sizeof(Walker));
  sWalker.xExprCallback = resolveRemoveWindowsCb;
  sWalker.u.pSelect = pSelect;
  sqlite3WalkExpr(&sWalker, pExpr);
}