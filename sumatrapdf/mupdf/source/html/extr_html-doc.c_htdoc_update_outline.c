#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {struct TYPE_4__* next; struct TYPE_4__* down; int /*<<< orphan*/  y; int /*<<< orphan*/  x; int /*<<< orphan*/  uri; int /*<<< orphan*/  page; } ;
typedef  TYPE_1__ fz_outline ;
typedef  int /*<<< orphan*/  fz_document ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  page; } ;

/* Variables and functions */
 TYPE_3__ htdoc_resolve_link (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
htdoc_update_outline(fz_context *ctx, fz_document *doc, fz_outline *node)
{
	while (node)
	{
		node->page = htdoc_resolve_link(ctx, doc, node->uri, &node->x, &node->y).page;
		htdoc_update_outline(ctx, doc, node->down);
		node = node->next;
	}
}