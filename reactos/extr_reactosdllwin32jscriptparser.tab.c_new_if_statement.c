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
typedef  int /*<<< orphan*/  statement_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_3__ {int /*<<< orphan*/  stat; int /*<<< orphan*/ * else_stat; int /*<<< orphan*/ * if_stat; int /*<<< orphan*/ * expr; } ;
typedef  TYPE_1__ if_statement_t ;
typedef  int /*<<< orphan*/  expression_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_IF ; 
 TYPE_1__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_if_statement(parser_ctx_t *ctx, expression_t *expr, statement_t *if_stat, statement_t *else_stat)
{
    if_statement_t *ret;

    ret = new_statement(ctx, STAT_IF, sizeof(*ret));
    if(!ret)
        return NULL;

    ret->expr = expr;
    ret->if_stat = if_stat;
    ret->else_stat = else_stat;

    return &ret->stat;
}