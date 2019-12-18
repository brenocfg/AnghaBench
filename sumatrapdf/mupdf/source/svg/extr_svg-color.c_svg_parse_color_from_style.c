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
typedef  int /*<<< orphan*/  svg_document ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ strncmp (char const*,char*,int) ; 
 char* strstr (char const*,char*) ; 
 scalar_t__ svg_is_whitespace (char const) ; 
 int /*<<< orphan*/  svg_parse_color (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,float*) ; 

void
svg_parse_color_from_style(fz_context *ctx, svg_document *doc, const char *str,
	int *fill_is_set, float fill[3],
	int *stroke_is_set, float stroke[3])
{
	const char *p;

	p = strstr(str, "fill:");
	if (p)
	{
		p += 5;
		while (*p && svg_is_whitespace(*p))
			++p;
		if (strncmp(p, "none", 4) != 0)
		{
			svg_parse_color(ctx, doc, p, fill);
			*fill_is_set = 1;
		}
	}

	p = strstr(str, "stroke:");
	if (p)
	{
		p += 7;
		while (*p && svg_is_whitespace(*p))
			++p;
		if (strncmp(p, "none", 4) != 0)
		{
			svg_parse_color(ctx, doc, p, stroke);
			*stroke_is_set = 1;
		}
	}
}