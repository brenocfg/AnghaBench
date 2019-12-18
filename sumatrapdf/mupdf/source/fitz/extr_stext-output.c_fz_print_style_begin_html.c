#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  font_family_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,int,int) ; 
 int fz_font_is_bold (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_font_is_italic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_font_is_monospaced (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_font_is_serif (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
fz_print_style_begin_html(fz_context *ctx, fz_output *out, fz_font *font, float size, int sup, int color)
{
	char family[80];

	int is_bold = fz_font_is_bold(ctx, font);
	int is_italic = fz_font_is_italic(ctx, font);
	int is_serif = fz_font_is_serif(ctx, font);
	int is_mono = fz_font_is_monospaced(ctx, font);

	font_family_name(ctx, font, family, sizeof family, is_mono, is_serif);

	if (sup) fz_write_string(ctx, out, "<sup>");
	if (is_mono) fz_write_string(ctx, out, "<tt>");
	if (is_bold) fz_write_string(ctx, out, "<b>");
	if (is_italic) fz_write_string(ctx, out, "<i>");
	fz_write_printf(ctx, out, "<span style=\"font-family:%s;font-size:%gpt", family, size);
	if (color != 0)
		fz_write_printf(ctx, out, ";color:#%06x", color);
	fz_write_printf(ctx, out, "\">");
}