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
typedef  int /*<<< orphan*/  CPValue ;
typedef  int /*<<< orphan*/  CPState ;

/* Variables and functions */
 int /*<<< orphan*/  cp_expr_infix (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  cp_expr_unary (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cp_expr_sub(CPState *cp, CPValue *k, int pri)
{
  cp_expr_unary(cp, k);
  cp_expr_infix(cp, k, pri);
}