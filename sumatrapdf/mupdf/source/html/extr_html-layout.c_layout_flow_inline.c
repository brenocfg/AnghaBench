#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {struct TYPE_6__* next; struct TYPE_6__* down; int /*<<< orphan*/  em; TYPE_1__* style; int /*<<< orphan*/  y; } ;
typedef  TYPE_2__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_5__ {int /*<<< orphan*/  font_size; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_from_css_number (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void layout_flow_inline(fz_context *ctx, fz_html_box *box, fz_html_box *top)
{
	while (box)
	{
		box->y = top->y;
		box->em = fz_from_css_number(box->style->font_size, top->em, top->em, top->em);
		if (box->down)
			layout_flow_inline(ctx, box->down, box);
		box = box->next;
	}
}