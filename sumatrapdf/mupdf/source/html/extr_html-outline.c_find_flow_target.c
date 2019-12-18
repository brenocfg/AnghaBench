#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {float y; struct TYPE_5__* next; TYPE_1__* box; } ;
typedef  TYPE_2__ fz_html_flow ;
struct TYPE_4__ {scalar_t__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static float
find_flow_target(fz_html_flow *flow, const char *id)
{
	while (flow)
	{
		if (flow->box->id && !strcmp(id, flow->box->id))
			return flow->y;
		flow = flow->next;
	}
	return -1;
}