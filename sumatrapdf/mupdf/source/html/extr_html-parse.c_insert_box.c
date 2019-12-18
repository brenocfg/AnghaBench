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
struct TYPE_4__ {int type; struct TYPE_4__* next; struct TYPE_4__* down; struct TYPE_4__* up; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void insert_box(fz_context *ctx, fz_html_box *box, int type, fz_html_box *top)
{
	box->type = type;

	box->up = top;

	if (top)
	{
		/* Here 'next' really means 'last of my children'. This will
		 * be fixed up in a pass at the end of parsing. */
		if (!top->next)
		{
			top->down = top->next = box;
		}
		else
		{
			top->next->next = box;
			/* Here next actually means next */
			top->next = box;
		}
	}
}