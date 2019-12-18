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
struct TYPE_4__ {float y; struct TYPE_4__* next; } ;
typedef  TYPE_1__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static fz_html_flow *
make_flow_bookmark(fz_context *ctx, fz_html_flow *flow, float y)
{
	while (flow)
	{
		if (flow->y >= y)
			return flow;
		flow = flow->next;
	}
	return NULL;
}