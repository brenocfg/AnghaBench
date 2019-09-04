#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  parser_ctx_t ;
typedef  int /*<<< orphan*/  expression_t ;
struct TYPE_4__ {int /*<<< orphan*/  tail; int /*<<< orphan*/  head; } ;
typedef  TYPE_1__ element_list_t ;

/* Variables and functions */
 int /*<<< orphan*/  new_array_element (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 TYPE_1__* parser_alloc_tmp (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static element_list_t *new_element_list(parser_ctx_t *ctx, int elision, expression_t *expr)
{
    element_list_t *ret = parser_alloc_tmp(ctx, sizeof(element_list_t));

    ret->head = ret->tail = new_array_element(ctx, elision, expr);

    return ret;
}