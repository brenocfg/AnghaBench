#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  hb_buffer_t ;
struct TYPE_9__ {int em; int w; scalar_t__ y; scalar_t__ b; scalar_t__ type; scalar_t__ x; struct TYPE_9__* next; struct TYPE_9__* down; TYPE_1__* style; } ;
typedef  TYPE_2__ fz_html_box ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_8__ {int /*<<< orphan*/  font_size; int /*<<< orphan*/  width; } ;

/* Variables and functions */
 scalar_t__ BOX_BLOCK ; 
 scalar_t__ BOX_FLOW ; 
 void* fz_from_css_number (int /*<<< orphan*/ ,int,int,int) ; 
 int /*<<< orphan*/  layout_block (int /*<<< orphan*/ *,TYPE_2__*,int,scalar_t__,scalar_t__*,float,float,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  layout_flow (int /*<<< orphan*/ *,TYPE_2__*,TYPE_2__*,float,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void layout_table(fz_context *ctx, fz_html_box *box, fz_html_box *top, float page_h, hb_buffer_t *hb_buf)
{
	fz_html_box *row, *cell, *child;
	int col, ncol = 0;

	box->em = fz_from_css_number(box->style->font_size, top->em, top->em, top->em);
	box->x = top->x;
	box->w = fz_from_css_number(box->style->width, box->em, top->w, top->w);
	box->y = box->b = top->b;

	for (row = box->down; row; row = row->next)
	{
		col = 0;
		for (cell = row->down; cell; cell = cell->next)
			++col;
		if (col > ncol)
			ncol = col;
	}

	for (row = box->down; row; row = row->next)
	{
		col = 0;

		row->em = fz_from_css_number(row->style->font_size, box->em, box->em, box->em);
		row->x = box->x;
		row->w = box->w;
		row->y = row->b = box->b;

		for (cell = row->down; cell; cell = cell->next)
		{
			float colw = row->w / ncol; // TODO: proper calculation

			cell->em = fz_from_css_number(cell->style->font_size, row->em, row->em, row->em);
			cell->y = cell->b = row->y;
			cell->x = row->x + col * colw;
			cell->w = colw;

			for (child = cell->down; child; child = child->next)
			{
				if (child->type == BOX_BLOCK)
					layout_block(ctx, child, cell->em, cell->x, &cell->b, cell->w, page_h, 0, hb_buf);
				else if (child->type == BOX_FLOW)
					layout_flow(ctx, child, cell, page_h, hb_buf);
				cell->b = child->b;
			}

			if (cell->b > row->b)
				row->b = cell->b;

			++col;
		}

		box->b = row->b;
	}
}