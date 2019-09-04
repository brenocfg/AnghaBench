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
struct TYPE_5__ {int /*<<< orphan*/  expr; int /*<<< orphan*/ * property_list; } ;
typedef  TYPE_1__ property_value_expression_t ;
struct TYPE_6__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_2__ property_list_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
typedef  int /*<<< orphan*/  expression_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_PROPVAL ; 
 TYPE_1__* new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static expression_t *new_prop_and_value_expression(parser_ctx_t *ctx, property_list_t *property_list)
{
    property_value_expression_t *ret = new_expression(ctx, EXPR_PROPVAL, sizeof(*ret));

    ret->property_list = property_list ? property_list->head : NULL;

    return &ret->expr;
}