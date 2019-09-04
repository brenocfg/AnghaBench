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
typedef  int /*<<< orphan*/  source_elements_t ;
typedef  int /*<<< orphan*/  parser_ctx_t ;
struct TYPE_5__ {int /*<<< orphan*/ * head; } ;
typedef  TYPE_1__ parameter_list_t ;
struct TYPE_6__ {int /*<<< orphan*/  expr; int /*<<< orphan*/ * next; int /*<<< orphan*/  src_len; int /*<<< orphan*/  const* src_str; int /*<<< orphan*/  const* event_target; int /*<<< orphan*/ * source_elements; int /*<<< orphan*/ * parameter_list; int /*<<< orphan*/  const* identifier; } ;
typedef  TYPE_2__ function_expression_t ;
typedef  int /*<<< orphan*/  expression_t ;
typedef  int /*<<< orphan*/  WCHAR ;
typedef  int /*<<< orphan*/  DWORD ;

/* Variables and functions */
 int /*<<< orphan*/  EXPR_FUNC ; 
 TYPE_2__* new_expression (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static expression_t *new_function_expression(parser_ctx_t *ctx, const WCHAR *identifier, parameter_list_t *parameter_list,
    source_elements_t *source_elements, const WCHAR *event_target, const WCHAR *src_str, DWORD src_len)
{
    function_expression_t *ret = new_expression(ctx, EXPR_FUNC, sizeof(*ret));

    ret->identifier = identifier;
    ret->parameter_list = parameter_list ? parameter_list->head : NULL;
    ret->source_elements = source_elements;
    ret->event_target = event_target;
    ret->src_str = src_str;
    ret->src_len = src_len;
    ret->next = NULL;

    return &ret->expr;
}