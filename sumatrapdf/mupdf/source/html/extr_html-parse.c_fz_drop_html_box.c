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
struct TYPE_3__ {struct TYPE_3__* down; int /*<<< orphan*/  flow_head; struct TYPE_3__* next; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fz_drop_html_flow (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void fz_drop_html_box(fz_context *ctx, fz_html_box *box)
{
	while (box)
	{
		fz_html_box *next = box->next;
		fz_drop_html_flow(ctx, box->flow_head);
		fz_drop_html_box(ctx, box->down);
		box = next;
	}
}