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
struct TYPE_3__ {int /*<<< orphan*/  expr; int /*<<< orphan*/  const* identifier; int /*<<< orphan*/ * expression; } ;
typedef  TYPE_1__ member_expression_t ;
typedef  int /*<<< orphan*/  expression_t ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_MEMBER ; 
 TYPE_1__* new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static expression_t *new_member_expression(parser_ctx_t *ctx, expression_t *expression, const WCHAR *identifier)
{
    member_expression_t *ret = new_expression(ctx, EXPR_MEMBER, sizeof(*ret));

    ret->expression = expression;
    ret->identifier = identifier;

    return &ret->expr;
}