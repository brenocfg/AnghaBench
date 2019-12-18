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
typedef  int /*<<< orphan*/  uni_buf ;
typedef  int /*<<< orphan*/  fz_pool ;
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* down; scalar_t__ flow_head; int /*<<< orphan*/  markup_dir; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  detect_flow_directionality (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static void
detect_box_directionality(fz_context *ctx, fz_pool *pool, uni_buf *buffer, fz_html_box *box)
{
	while (box)
	{
		if (box->flow_head)
			box->markup_dir = detect_flow_directionality(ctx, pool, buffer, box->markup_dir, box->flow_head);
		detect_box_directionality(ctx, pool, buffer, box->down);
		box = box->next;
	}
}