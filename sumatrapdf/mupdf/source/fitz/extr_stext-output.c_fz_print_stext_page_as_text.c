#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_6__ ;
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {TYPE_6__* first_block; } ;
typedef  TYPE_3__ fz_stext_page ;
struct TYPE_11__ {TYPE_5__* first_char; struct TYPE_11__* next; } ;
typedef  TYPE_4__ fz_stext_line ;
struct TYPE_12__ {int /*<<< orphan*/  c; struct TYPE_12__* next; } ;
typedef  TYPE_5__ fz_stext_char ;
struct TYPE_8__ {TYPE_4__* first_line; } ;
struct TYPE_9__ {TYPE_1__ t; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_2__ u; struct TYPE_13__* next; } ;
typedef  TYPE_6__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ FZ_STEXT_BLOCK_TEXT ; 
 int fz_runetochar (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void
fz_print_stext_page_as_text(fz_context *ctx, fz_output *out, fz_stext_page *page)
{
	fz_stext_block *block;
	fz_stext_line *line;
	fz_stext_char *ch;
	char utf[10];
	int i, n;

	for (block = page->first_block; block; block = block->next)
	{
		if (block->type == FZ_STEXT_BLOCK_TEXT)
		{
			for (line = block->u.t.first_line; line; line = line->next)
			{
				for (ch = line->first_char; ch; ch = ch->next)
				{
					n = fz_runetochar(utf, ch->c);
					for (i = 0; i < n; i++)
						fz_write_byte(ctx, out, utf[i]);
				}
				fz_write_string(ctx, out, "\n");
			}
			fz_write_string(ctx, out, "\n");
		}
	}
}