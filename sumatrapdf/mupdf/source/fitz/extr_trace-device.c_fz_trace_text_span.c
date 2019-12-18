#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/  d; int /*<<< orphan*/  c; int /*<<< orphan*/  b; int /*<<< orphan*/  a; } ;
struct TYPE_7__ {int len; TYPE_2__* items; int /*<<< orphan*/  font; TYPE_1__ trm; int /*<<< orphan*/  bidi_level; int /*<<< orphan*/  wmode; } ;
typedef  TYPE_3__ fz_text_span ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_6__ {int ucs; scalar_t__ gid; int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;

/* Variables and functions */
 int /*<<< orphan*/  fz_font_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_get_glyph_name (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__,char*,int) ; 
 int /*<<< orphan*/  fz_trace_indent (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  isxmlmeta (int) ; 

__attribute__((used)) static void
fz_trace_text_span(fz_context *ctx, fz_output *out, fz_text_span *span, int depth)
{
	int i;
	fz_trace_indent(ctx, out, depth);
	fz_write_printf(ctx, out, "<span font=\"%s\" wmode=\"%d\" bidi=\"%d\"", fz_font_name(ctx, span->font), span->wmode, span->bidi_level);
	fz_write_printf(ctx, out, " trm=\"%g %g %g %g\">\n", span->trm.a, span->trm.b, span->trm.c, span->trm.d);
	for (i = 0; i < span->len; i++)
	{
		char name[32];

		fz_trace_indent(ctx, out, depth+1);
		if (span->items[i].ucs == -1)
			fz_write_printf(ctx, out, "<g unicode=\"-1\"");
		else if (!isxmlmeta(span->items[i].ucs))
			fz_write_printf(ctx, out, "<g unicode=\"%c\"", span->items[i].ucs);
		else
			fz_write_printf(ctx, out, "<g unicode=\"U+%04x\"", span->items[i].ucs);

		if (span->items[i].gid >= 0)
		{
			fz_get_glyph_name(ctx, span->font, span->items[i].gid, name, sizeof name);
			fz_write_printf(ctx, out, " glyph=\"%s\"", name);
		}
		else
			fz_write_printf(ctx, out, " glyph=\"-1\"");

		fz_write_printf(ctx, out, " x=\"%g\" y=\"%g\" />\n", span->items[i].x, span->items[i].y);
	}
	fz_trace_indent(ctx, out, depth);
	fz_write_printf(ctx, out, "</span>\n");
}