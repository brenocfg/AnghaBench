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
typedef  int /*<<< orphan*/  xps_document ;
struct TYPE_4__ {struct TYPE_4__* down; struct TYPE_4__* next; } ;
typedef  TYPE_1__ fz_outline ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static fz_outline *
xps_lookup_last_outline_at_level(fz_context *ctx, xps_document *doc, fz_outline *node, int level, int target_level)
{
	while (node->next)
		node = node->next;
	if (level == target_level || !node->down)
		return node;
	return xps_lookup_last_outline_at_level(ctx, doc, node->down, level + 1, target_level);
}