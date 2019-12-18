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
 float break_simple_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,float,char const*,char const**,float) ; 
 int /*<<< orphan*/  fz_append_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,float,float) ; 
 int /*<<< orphan*/  fz_append_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  write_simple_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*) ; 

__attribute__((used)) static void
write_simple_string_with_quadding(fz_context *ctx, fz_buffer *buf, fz_font *font, float size,
	const char *a, float maxw, int q)
{
	const char *b;
	float px = 0, x = 0, w;
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
				fz_append_printf(ctx, buf, "%g %g Td ", x - px, -size);
			}
			if (b[-1] == '\n' || b[-1] == '\r')
				write_simple_string(ctx, buf, a, b-1);
			else
				write_simple_string(ctx, buf, a, b);
			a = b;
			px = x;
			fz_append_string(ctx, buf, (q > 0) ? "Tj\n" : "'\n");
		}
	}
}