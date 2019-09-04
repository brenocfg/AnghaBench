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
typedef  int /*<<< orphan*/  parser_ctx_t ;
typedef  int /*<<< orphan*/  expression_t ;
struct TYPE_5__ {int /*<<< orphan*/  expr; int /*<<< orphan*/ * argument_list; int /*<<< orphan*/ * expression; } ;
typedef  TYPE_1__ call_expression_t ;
struct TYPE_6__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_2__ argument_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_NEW ; 
 TYPE_1__* new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static expression_t *new_new_expression(parser_ctx_t *ctx, expression_t *expression, argument_list_t *argument_list)
{
    call_expression_t *ret = new_expression(ctx, EXPR_NEW, sizeof(*ret));

    ret->expression = expression;
    ret->argument_list = argument_list ? argument_list->head : NULL;

    return &ret->expr;
}