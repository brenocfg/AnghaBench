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
struct TYPE_5__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ variable_list_t ;
typedef  int /*<<< orphan*/  statement_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_6__ {int /*<<< orphan*/  stat; int /*<<< orphan*/ * statement; int /*<<< orphan*/ * end_expr; int /*<<< orphan*/ * expr; int /*<<< orphan*/ * begin_expr; int /*<<< orphan*/ * variable_list; } ;
typedef  TYPE_2__ for_statement_t ;
typedef  int /*<<< orphan*/  expression_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_FOR ; 
 TYPE_2__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_for_statement(parser_ctx_t *ctx, variable_list_t *variable_list, expression_t *begin_expr,
        expression_t *expr, expression_t *end_expr, statement_t *statement)
{
    for_statement_t *ret;

    ret = new_statement(ctx, STAT_FOR, sizeof(*ret));
    if(!ret)
        return NULL;

    ret->variable_list = variable_list ? variable_list->head : NULL;
    ret->begin_expr = begin_expr;
    ret->expr = expr;
    ret->end_expr = end_expr;
    ret->statement = statement;

    return &ret->stat;
}