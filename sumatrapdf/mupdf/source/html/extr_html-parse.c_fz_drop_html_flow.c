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
struct TYPE_4__ {int /*<<< orphan*/  image; } ;
struct TYPE_5__ {scalar_t__ type; TYPE_1__ content; struct TYPE_5__* next; } ;
typedef  TYPE_2__ fz_html_flow ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FLOW_IMAGE ; 
 int /*<<< orphan*/  fz_drop_image (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fz_drop_html_flow(fz_context *ctx, fz_html_flow *flow)
{
	while (flow)
	{
		fz_html_flow *next = flow->next;
		if (flow->type == FLOW_IMAGE)
			fz_drop_image(ctx, flow->content.image);
		flow = next;
	}
}