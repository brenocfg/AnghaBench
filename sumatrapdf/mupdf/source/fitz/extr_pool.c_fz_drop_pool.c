#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {struct TYPE_5__* next; struct TYPE_5__* head; } ;
typedef  TYPE_1__ fz_pool_node ;
typedef  TYPE_1__ fz_pool ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,TYPE_1__*) ; 

void fz_drop_pool(fz_context *ctx, fz_pool *pool)
{
	fz_pool_node *node;

	if (!pool)
		return;

	node = pool->head;
	while (node)
	{
		fz_pool_node *next = node->next;
		fz_free(ctx, node);
		node = next;
	}
	fz_free(ctx, pool);
}