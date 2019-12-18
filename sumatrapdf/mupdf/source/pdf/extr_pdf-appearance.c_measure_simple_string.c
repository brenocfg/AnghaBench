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

/* Variables and functions */
 int REPLACEMENT ; 
 scalar_t__ fz_advance_glyph (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 int fz_encode_character (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int fz_windows_1252_from_unicode (int) ; 

__attribute__((used)) static float
measure_simple_string(fz_context *ctx, fz_font *font, const char *text)
{
	float w = 0;
	while (*text)
	{
		int c, g;
		text += fz_chartorune(&c, text);
		c = fz_windows_1252_from_unicode(c);
		if (c < 0) c = REPLACEMENT;
		g = fz_encode_character(ctx, font, c);
		w += fz_advance_glyph(ctx, font, g, 0);
	}
	return w;
}