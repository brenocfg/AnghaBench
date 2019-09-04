#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parser_ctx_t ;
typedef  int /*<<< orphan*/  expression_type_t ;
typedef  int /*<<< orphan*/  expression_t ;
struct TYPE_3__ {int /*<<< orphan*/  expr; int /*<<< orphan*/ * right; int /*<<< orphan*/ * left; } ;
typedef  TYPE_1__ binary_expression_t ;

/* Variables and functions */
 TYPE_1__* new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static expression_t *new_binary_expression(parser_ctx_t *ctx, expression_type_t type, expression_t *left, expression_t *right)
{
    binary_expression_t *expr;

    expr = new_expression(ctx, type, sizeof(*expr));
    if(!expr)
        return NULL;

    expr->left = left;
    expr->right = right;
    return &expr->expr;
}