#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  test_context ;
struct TYPE_6__ {int can_pushdown; } ;
typedef  TYPE_1__ QualPushdownContext ;
typedef  int /*<<< orphan*/  Node ;
typedef  int /*<<< orphan*/  Expr ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (TYPE_1__*,TYPE_1__ const*,int) ; 
 scalar_t__ modify_expression (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static Expr *
get_pushdownsafe_expr(const QualPushdownContext *input_context, Expr *input)
{
	/* do not mess up the input_context, so create a new one */
	QualPushdownContext test_context;
	Expr *expr;

	memcpy(&test_context, input_context, sizeof(test_context));
	test_context.can_pushdown = true;
	expr = (Expr *) modify_expression((Node *) input, &test_context);
	if (test_context.can_pushdown)
		return expr;
	return NULL;
}