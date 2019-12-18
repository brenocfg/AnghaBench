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
typedef  int /*<<< orphan*/  fz_layout_block ;
typedef  int /*<<< orphan*/  fz_font ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float break_simple_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,char const*,char const**,float) ; 
 int /*<<< orphan*/  fz_add_layout_line (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float,float,char const*) ; 
 int /*<<< orphan*/  layout_simple_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,float,float,char const*,char const*) ; 

__attribute__((used)) static void
layout_simple_string_with_quadding(fz_context *ctx, fz_layout_block *out,
	fz_font *font, float size, float lineheight,
	float xorig, float y, const char *a, float maxw, int q)
{
	const char *b;
	float x = 0, w;
	int add_line_at_end = 0;

	if (!*a)
		add_line_at_end = 1;

	while (*a)
	{
		w = break_simple_string(ctx, font, size, a, &b, maxw);
		if (b > a)
		{
			if (q > 0)
			{
				if (q == 1)
					x = (maxw - w) / 2;
				else
					x = (maxw - w);
			}
			if (b[-1] == '\n' || b[-1] == '\r')
			{
				layout_simple_string(ctx, out, font, size, xorig+x, y, a, b-1);
				add_line_at_end = 1;
			}
			else
			{
				layout_simple_string(ctx, out, font, size, xorig+x, y, a, b);
				add_line_at_end = 0;
			}
			a = b;
			y -= lineheight;
		}
	}
	if (add_line_at_end)
		fz_add_layout_line(ctx, out, xorig, y, size, a);
}