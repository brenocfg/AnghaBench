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
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int REPLACEMENT ; 
 int fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_append_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 int fz_encode_character (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_windows_1252_from_unicode (int) ; 

__attribute__((used)) static void
write_comb_string(fz_context *ctx, fz_buffer *buf, const char *a, const char *b, fz_font *font, float cell_w)
{
	float gw, pad, carry = 0;
	fz_append_byte(ctx, buf, '[');
	while (a < b)
	{
		int c, g;

		a += fz_chartorune(&c, a);
		c = fz_windows_1252_from_unicode(c);
		if (c < 0) c = REPLACEMENT;

		g = fz_encode_character(ctx, font, c);
		gw = fz_advance_glyph(ctx, font, g, 0) * 1000;
		pad = (cell_w - gw) / 2;
		fz_append_printf(ctx, buf, "%g", -(carry + pad));
		carry = pad;

		fz_append_byte(ctx, buf, '(');
		if (c == '(' || c == ')' || c == '\\')
			fz_append_byte(ctx, buf, '\\');
		fz_append_byte(ctx, buf, c);
		fz_append_byte(ctx, buf, ')');
	}
	fz_append_string(ctx, buf, "] TJ\n");
}