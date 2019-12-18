#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct callbacks {int /*<<< orphan*/  arg; int /*<<< orphan*/  (* on_line ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ;int /*<<< orphan*/  (* on_char ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ;} ;
struct TYPE_14__ {TYPE_6__* first_block; } ;
typedef  TYPE_3__ fz_stext_page ;
struct TYPE_15__ {TYPE_5__* first_char; struct TYPE_15__* next; } ;
typedef  TYPE_4__ fz_stext_line ;
struct TYPE_16__ {struct TYPE_16__* next; } ;
typedef  TYPE_5__ fz_stext_char ;
struct TYPE_12__ {TYPE_4__* first_line; } ;
struct TYPE_13__ {TYPE_1__ t; } ;
struct TYPE_17__ {scalar_t__ type; TYPE_2__ u; struct TYPE_17__* next; } ;
typedef  TYPE_6__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_point ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_STEXT_BLOCK_TEXT ; 
 int find_closest_in_page (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__*) ; 

__attribute__((used)) static void
fz_enumerate_selection(fz_context *ctx, fz_stext_page *page, fz_point a, fz_point b, struct callbacks *cb)
{
	fz_stext_block *block;
	fz_stext_line *line;
	fz_stext_char *ch;
	int idx, start, end;
	int inside;

	start = find_closest_in_page(page, a);
	end = find_closest_in_page(page, b);

	if (start > end)
		idx = start, start = end, end = idx;

	if (start == end)
		return;

	inside = 0;
	idx = 0;
	for (block = page->first_block; block; block = block->next)
	{
		if (block->type != FZ_STEXT_BLOCK_TEXT)
			continue;
		for (line = block->u.t.first_line; line; line = line->next)
		{
			for (ch = line->first_char; ch; ch = ch->next)
			{
				if (!inside)
					if (idx == start)
						inside = 1;
				if (inside)
					cb->on_char(ctx, cb->arg, line, ch);
				if (++idx == end)
					return;
			}
			if (inside)
				cb->on_line(ctx, cb->arg, line);
		}
	}
}