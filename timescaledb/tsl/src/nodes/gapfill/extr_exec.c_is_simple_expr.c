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
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  is_simple_expr_walker (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static bool
is_simple_expr(Expr *node)
{
	/*
	 * since expression_tree_walker does early exit on true and we use that to
	 * skip processing on first non-simple expression we invert return value
	 * from expression_tree_walker here
	 */
	return !is_simple_expr_walker((Node *) node, NULL);
}