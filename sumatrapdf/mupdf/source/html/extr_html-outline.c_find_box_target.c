#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float y; } ;
typedef  TYPE_1__ fz_html_flow ;
struct TYPE_7__ {float y; scalar_t__ type; struct TYPE_7__* next; struct TYPE_7__* down; int /*<<< orphan*/  flow_head; scalar_t__ id; } ;
typedef  TYPE_2__ fz_html_box ;

/* Variables and functions */
 scalar_t__ BOX_FLOW ; 
 TYPE_1__* find_first_content (TYPE_2__*) ; 
 float find_flow_target (int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  strcmp (char const*,scalar_t__) ; 

__attribute__((used)) static float
find_box_target(fz_html_box *box, const char *id)
{
	float y;
	while (box)
	{
		if (box->id && !strcmp(id, box->id))
		{
			fz_html_flow *flow = find_first_content(box);
			if (flow)
				return flow->y;
			return box->y;
		}
		if (box->type == BOX_FLOW)
		{
			y = find_flow_target(box->flow_head, id);
			if (y >= 0)
				return y;
		}
		else
		{
			y = find_box_target(box->down, id);
			if (y >= 0)
				return y;
		}
		box = box->next;
	}
	return -1;
}