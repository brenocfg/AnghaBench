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
struct TYPE_5__ {TYPE_2__* tail; } ;
typedef  TYPE_1__ argument_list_t ;
struct TYPE_6__ {struct TYPE_6__* next; } ;

/* Variables and functions */
 TYPE_2__* new_argument (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static argument_list_t *argument_list_add(parser_ctx_t *ctx, argument_list_t *list, expression_t *expr)
{
    list->tail = list->tail->next = new_argument(ctx, expr);

    return list;
}