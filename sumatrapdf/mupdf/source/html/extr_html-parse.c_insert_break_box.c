#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ type; struct TYPE_7__* up; } ;
typedef  TYPE_1__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ BOX_BLOCK ; 
 int /*<<< orphan*/  BOX_BREAK ; 
 scalar_t__ BOX_FLOW ; 
 scalar_t__ BOX_INLINE ; 
 int /*<<< orphan*/  insert_box (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ,TYPE_1__*) ; 

__attribute__((used)) static fz_html_box *insert_break_box(fz_context *ctx, fz_html_box *box, fz_html_box *top)
{
	if (top->type == BOX_BLOCK)
	{
		insert_box(ctx, box, BOX_BREAK, top);
	}
	else if (top->type == BOX_FLOW)
	{
		while (top->type != BOX_BLOCK)
			top = top->up;
		insert_box(ctx, box, BOX_BREAK, top);
	}
	else if (top->type == BOX_INLINE)
	{
		while (top->type != BOX_BLOCK)
			top = top->up;
		insert_box(ctx, box, BOX_BREAK, top);
	}
	return top;
}