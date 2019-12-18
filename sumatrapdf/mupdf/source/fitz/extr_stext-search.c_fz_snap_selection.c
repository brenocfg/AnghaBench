#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_8__ ;
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_15__ {TYPE_7__* first_block; } ;
typedef  TYPE_4__ fz_stext_page ;
struct TYPE_16__ {TYPE_6__* first_char; struct TYPE_16__* next; } ;
typedef  TYPE_5__ fz_stext_line ;
struct TYPE_14__ {void* lr; void* ur; void* ul; void* ll; } ;
struct TYPE_17__ {char c; TYPE_3__ quad; struct TYPE_17__* next; void* origin; } ;
typedef  TYPE_6__ fz_stext_char ;
struct TYPE_12__ {TYPE_5__* first_line; } ;
struct TYPE_13__ {TYPE_1__ t; } ;
struct TYPE_18__ {scalar_t__ type; TYPE_2__ u; struct TYPE_18__* next; } ;
typedef  TYPE_7__ fz_stext_block ;
struct TYPE_19__ {void* ur; void* lr; void* ul; void* ll; } ;
typedef  TYPE_8__ fz_quad ;
typedef  void* fz_point ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_SELECT_CHARS ; 
 int FZ_SELECT_LINES ; 
 int FZ_SELECT_WORDS ; 
 scalar_t__ FZ_STEXT_BLOCK_TEXT ; 
 int find_closest_in_page (TYPE_4__*,void*) ; 

fz_quad
fz_snap_selection(fz_context *ctx, fz_stext_page *page, fz_point *a, fz_point *b, int mode)
{
	fz_stext_block *block;
	fz_stext_line *line;
	fz_stext_char *ch;
	fz_quad handles;
	int idx, start, end;
	int pc;

	start = find_closest_in_page(page, *a);
	end = find_closest_in_page(page, *b);

	if (start > end)
		idx = start, start = end, end = idx;

	handles.ll = handles.ul = *a;
	handles.lr = handles.ur = *b;

	idx = 0;
	for (block = page->first_block; block; block = block->next)
	{
		if (block->type != FZ_STEXT_BLOCK_TEXT)
			continue;
		for (line = block->u.t.first_line; line; line = line->next)
		{
			pc = '\n';
			for (ch = line->first_char; ch; ch = ch->next)
			{
				if (idx <= start)
				{
					if (mode == FZ_SELECT_CHARS
						|| (mode == FZ_SELECT_WORDS && (pc == ' ' || pc == '\n'))
						|| (mode == FZ_SELECT_LINES && (pc == '\n')))
					{
						handles.ll = ch->quad.ll;
						handles.ul = ch->quad.ul;
						*a = ch->origin;
					}
				}
				if (idx >= end)
				{
					if (mode == FZ_SELECT_CHARS
						|| (mode == FZ_SELECT_WORDS && (ch->c == ' ')))
					{
						handles.lr = ch->quad.ll;
						handles.ur = ch->quad.ul;
						*b = ch->origin;
						return handles;
					}
					if (!ch->next)
					{
						handles.lr = ch->quad.lr;
						handles.ur = ch->quad.ur;
						*b = ch->quad.lr;
						return handles;
					}
				}
				pc = ch->c;
				++idx;
			}
		}
	}

	return handles;
}