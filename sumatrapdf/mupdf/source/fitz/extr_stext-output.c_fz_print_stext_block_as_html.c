#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct TYPE_12__ {int x0; int y0; } ;
struct TYPE_13__ {TYPE_5__* first_char; TYPE_3__ bbox; struct TYPE_13__* next; } ;
typedef  TYPE_4__ fz_stext_line ;
struct TYPE_14__ {float size; int color; int c; int /*<<< orphan*/ * font; struct TYPE_14__* next; } ;
typedef  TYPE_5__ fz_stext_char ;
struct TYPE_10__ {TYPE_4__* first_line; } ;
struct TYPE_11__ {TYPE_1__ t; } ;
struct TYPE_15__ {TYPE_2__ u; } ;
typedef  TYPE_6__ fz_stext_block ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int detect_super_script (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  fz_print_style_begin_html (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int,int) ; 
 int /*<<< orphan*/  fz_print_style_end_html (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,int) ; 
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

void
fz_print_stext_block_as_html(fz_context *ctx, fz_output *out, fz_stext_block *block)
{
	fz_stext_line *line;
	fz_stext_char *ch;
	int x, y;

	fz_font *font = NULL;
	float size = 0;
	int sup = 0;
	int color = 0;

	for (line = block->u.t.first_line; line; line = line->next)
	{
		x = line->bbox.x0;
		y = line->bbox.y0;

		fz_write_printf(ctx, out, "<p style=\"position:absolute;white-space:pre;margin:0;padding:0;top:%dpt;left:%dpt\">", y, x);
		font = NULL;

		for (ch = line->first_char; ch; ch = ch->next)
		{
			int ch_sup = detect_super_script(line, ch);
			if (ch->font != font || ch->size != size || ch_sup != sup || ch->color != color)
			{
				if (font)
					fz_print_style_end_html(ctx, out, font, size, sup);
				font = ch->font;
				size = ch->size;
				color = ch->color;
				sup = ch_sup;
				fz_print_style_begin_html(ctx, out, font, size, sup, color);
			}

			switch (ch->c)
			{
			default:
				if (ch->c >= 32 && ch->c <= 127)
					fz_write_byte(ctx, out, ch->c);
				else
					fz_write_printf(ctx, out, "&#x%x;", ch->c);
				break;
			case '<': fz_write_string(ctx, out, "&lt;"); break;
			case '>': fz_write_string(ctx, out, "&gt;"); break;
			case '&': fz_write_string(ctx, out, "&amp;"); break;
			case '"': fz_write_string(ctx, out, "&quot;"); break;
			case '\'': fz_write_string(ctx, out, "&apos;"); break;
			}
		}

		if (font)
			fz_print_style_end_html(ctx, out, font, size, sup);

		fz_write_string(ctx, out, "</p>\n");
	}
}