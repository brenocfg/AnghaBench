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
struct fmt {int dummy; } ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int c ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,int) ; 
 int /*<<< orphan*/  fmt_puts (int /*<<< orphan*/ *,struct fmt*,char*) ; 

__attribute__((used)) static void fmt_str_out(fz_context *ctx, void *fmt_, const unsigned char *s, int n)
{
	struct fmt *fmt = (struct fmt *)fmt_;
	int i, c;

	for (i = 0; i < n; i++)
	{
		c = (unsigned char)s[i];
		if (c == '\n')
			fmt_puts(ctx, fmt, "\\n");
		else if (c == '\r')
			fmt_puts(ctx, fmt, "\\r");
		else if (c == '\t')
			fmt_puts(ctx, fmt, "\\t");
		else if (c == '\b')
			fmt_puts(ctx, fmt, "\\b");
		else if (c == '\f')
			fmt_puts(ctx, fmt, "\\f");
		else if (c == '(')
			fmt_puts(ctx, fmt, "\\(");
		else if (c == ')')
			fmt_puts(ctx, fmt, "\\)");
		else if (c == '\\')
			fmt_puts(ctx, fmt, "\\\\");
		else if (c < 32 || c >= 127) {
			fmt_putc(ctx, fmt, '\\');
			fmt_putc(ctx, fmt, '0' + ((c / 64) & 7));
			fmt_putc(ctx, fmt, '0' + ((c / 8) & 7));
			fmt_putc(ctx, fmt, '0' + ((c) & 7));
		}
		else
			fmt_putc(ctx, fmt, c);
	}
}