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
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int fz_peek_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

char *
fz_read_line(fz_context *ctx, fz_stream *stm, char *mem, size_t n)
{
	char *s = mem;
	int c = EOF;
	while (n > 1)
	{
		c = fz_read_byte(ctx, stm);
		if (c == EOF)
			break;
		if (c == '\r') {
			c = fz_peek_byte(ctx, stm);
			if (c == '\n')
				fz_read_byte(ctx, stm);
			break;
		}
		if (c == '\n')
			break;
		*s++ = c;
		n--;
	}
	if (n)
		*s = '\0';
	return (s == mem && c == EOF) ? NULL : mem;
}