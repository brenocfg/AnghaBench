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
typedef  int /*<<< orphan*/  fz_link ;
struct TYPE_3__ {struct TYPE_3__* next; struct TYPE_3__* down; scalar_t__ flow_head; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/ * load_link_flow (int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ *,int,float,char const*,char const*) ; 

__attribute__((used)) static fz_link *load_link_box(fz_context *ctx, fz_html_box *box, fz_link *head, int page, float page_h, const char *dir, const char *file)
{
	while (box)
	{
		if (box->flow_head)
			head = load_link_flow(ctx, box->flow_head, head, page, page_h, dir, file);
		if (box->down)
			head = load_link_box(ctx, box->down, head, page, page_h, dir, file);
		box = box->next;
	}
	return head;
}