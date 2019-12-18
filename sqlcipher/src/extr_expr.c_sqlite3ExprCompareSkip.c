#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int sqlite3ExprCompare (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  sqlite3ExprSkipCollate (int /*<<< orphan*/ *) ; 

int sqlite3ExprCompareSkip(Expr *pA, Expr *pB, int iTab){
  return sqlite3ExprCompare(0,
             sqlite3ExprSkipCollate(pA),
             sqlite3ExprSkipCollate(pB),
             iTab);
}