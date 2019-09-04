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
struct TYPE_3__ {int /*<<< orphan*/  stat; int /*<<< orphan*/ * case_list; int /*<<< orphan*/ * expr; } ;
typedef  TYPE_1__ switch_statement_t ;
typedef  int /*<<< orphan*/  statement_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
typedef  int /*<<< orphan*/  expression_t ;
typedef  int /*<<< orphan*/  case_clausule_t ;

/* Variables and functions */
 int /*<<< orphan*/  STAT_SWITCH ; 
 TYPE_1__* new_statement (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static statement_t *new_switch_statement(parser_ctx_t *ctx, expression_t *expr, case_clausule_t *case_list)
{
    switch_statement_t *ret;

    ret = new_statement(ctx, STAT_SWITCH, sizeof(*ret));
    if(!ret)
        return NULL;

    ret->expr = expr;
    ret->case_list = case_list;

    return &ret->stat;
}