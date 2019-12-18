#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_html_flow ;
struct TYPE_3__ {scalar_t__ type; struct TYPE_3__* next; struct TYPE_3__* down; int /*<<< orphan*/  flow_head; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ BOX_FLOW ; 
 scalar_t__ lookup_flow_bookmark (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
lookup_box_bookmark(fz_context *ctx, fz_html_box *box, fz_html_flow *mark)
{
	while (box)
	{
		if (box->type == BOX_FLOW)
		{
			if (lookup_flow_bookmark(ctx, box->flow_head, mark))
				return 1;
		}
		else
		{
			if (lookup_box_bookmark(ctx, box->down, mark))
				return 1;
		}
		box = box->next;
	}
	return 0;
}