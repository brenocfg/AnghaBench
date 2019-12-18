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
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_buffer ;

/* Variables and functions */
 int REPLACEMENT ; 
 int /*<<< orphan*/  fz_append_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  fz_chartorune (int*,char const*) ; 
 int fz_windows_1252_from_unicode (int) ; 

__attribute__((used)) static void
write_simple_string(fz_context *ctx, fz_buffer *buf, const char *a, const char *b)
{
	fz_append_byte(ctx, buf, '(');
	while (a < b)
	{
		int c;
		a += fz_chartorune(&c, a);
		c = fz_windows_1252_from_unicode(c);
		if (c < 0) c = REPLACEMENT;
		if (c == '(' || c == ')' || c == '\\')
			fz_append_byte(ctx, buf, '\\');
		fz_append_byte(ctx, buf, c);
	}
	fz_append_byte(ctx, buf, ')');
}