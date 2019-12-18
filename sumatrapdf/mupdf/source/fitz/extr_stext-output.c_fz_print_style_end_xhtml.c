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
 int fz_font_is_bold (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_font_is_italic (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_font_is_monospaced (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
fz_print_style_end_xhtml(fz_context *ctx, fz_output *out, fz_font *font, int sup)
{
	int is_mono = fz_font_is_monospaced(ctx, font);
	int is_bold = fz_font_is_bold(ctx, font);
	int is_italic = fz_font_is_italic(ctx, font);

	if (is_italic)
		fz_write_string(ctx, out, "</i>");
	if (is_bold)
		fz_write_string(ctx, out, "</b>");
	if (is_mono)
		fz_write_string(ctx, out, "</tt>");
	if (sup)
		fz_write_string(ctx, out, "</sup>");
}