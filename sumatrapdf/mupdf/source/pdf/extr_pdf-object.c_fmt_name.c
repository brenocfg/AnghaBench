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
typedef  int /*<<< orphan*/  pdf_obj ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  fmt_putc (int /*<<< orphan*/ *,struct fmt*,unsigned char) ; 
 scalar_t__ isdelim (unsigned char) ; 
 scalar_t__ iswhite (unsigned char) ; 
 scalar_t__ pdf_to_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fmt_name(fz_context *ctx, struct fmt *fmt, pdf_obj *obj)
{
	unsigned char *s = (unsigned char *) pdf_to_name(ctx, obj);
	int i, c;

	fmt_putc(ctx, fmt, '/');

	for (i = 0; s[i]; i++)
	{
		if (isdelim(s[i]) || iswhite(s[i]) ||
			s[i] == '#' || s[i] < 32 || s[i] >= 127)
		{
			fmt_putc(ctx, fmt, '#');
			c = (s[i] >> 4) & 0xf;
			fmt_putc(ctx, fmt, c < 0xA ? c + '0' : c + 'A' - 0xA);
			c = s[i] & 0xf;
			fmt_putc(ctx, fmt, c < 0xA ? c + '0' : c + 'A' - 0xA);
		}
		else
		{
			fmt_putc(ctx, fmt, s[i]);
		}
	}
}