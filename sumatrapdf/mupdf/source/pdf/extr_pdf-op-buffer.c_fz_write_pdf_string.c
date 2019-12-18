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
typedef  int /*<<< orphan*/  fz_context ;
typedef  size_t c ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 

__attribute__((used)) static void
fz_write_pdf_string(fz_context *ctx, fz_output *out, const unsigned char *str, int len)
{
	int i;

	for (i = 0; i < len; ++i)
		if (str[i] < 32 || str[i] >= 127)
			break;

	if (i < len)
	{
		fz_write_byte(ctx, out, '<');
		for (i = 0; i < len; ++i)
		{
			unsigned char c = str[i];
			fz_write_byte(ctx, out, "0123456789abcdef"[(c>>4)&15]);
			fz_write_byte(ctx, out, "0123456789abcdef"[(c)&15]);
		}
		fz_write_byte(ctx, out, '>');
	}
	else
	{
		fz_write_byte(ctx, out, '(');
		for (i = 0; i < len; ++i)
		{
			unsigned char c = str[i];
			if (c == '(' || c == ')' || c == '\\')
				fz_write_byte(ctx, out, '\\');
			fz_write_byte(ctx, out, c);
		}
		fz_write_byte(ctx, out, ')');
	}
}