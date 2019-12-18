#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_7__ ;
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_7__* first_block; } ;
typedef  TYPE_3__ fz_stext_page ;
struct TYPE_11__ {void* bbox; TYPE_6__* first_char; struct TYPE_11__* next; } ;
typedef  TYPE_4__ fz_stext_line ;
struct TYPE_12__ {TYPE_3__* page; } ;
typedef  TYPE_5__ fz_stext_device ;
struct TYPE_13__ {int /*<<< orphan*/  quad; struct TYPE_13__* next; } ;
typedef  TYPE_6__ fz_stext_char ;
struct TYPE_8__ {TYPE_4__* first_line; } ;
struct TYPE_9__ {TYPE_1__ t; } ;
struct TYPE_14__ {scalar_t__ type; void* bbox; TYPE_2__ u; struct TYPE_14__* next; } ;
typedef  TYPE_7__ fz_stext_block ;
typedef  void* fz_rect ;
typedef  int /*<<< orphan*/  fz_device ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_STEXT_BLOCK_TEXT ; 
 void* fz_rect_from_quad (int /*<<< orphan*/ ) ; 
 void* fz_union_rect (void*,void*) ; 

__attribute__((used)) static void
fz_stext_close_device(fz_context *ctx, fz_device *dev)
{
	fz_stext_device *tdev = (fz_stext_device*)dev;
	fz_stext_page *page = tdev->page;
	fz_stext_block *block;
	fz_stext_line *line;
	fz_stext_char *ch;

	for (block = page->first_block; block; block = block->next)
	{
		if (block->type != FZ_STEXT_BLOCK_TEXT)
			continue;
		for (line = block->u.t.first_line; line; line = line->next)
		{
			for (ch = line->first_char; ch; ch = ch->next)
			{
				fz_rect ch_box = fz_rect_from_quad(ch->quad);
				if (ch == line->first_char)
					line->bbox = ch_box;
				else
					line->bbox = fz_union_rect(line->bbox, ch_box);
			}
			block->bbox = fz_union_rect(block->bbox, line->bbox);
		}
	}

	/* TODO: smart sorting of blocks and lines in reading order */
	/* TODO: unicode NFC normalization */
}