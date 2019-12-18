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
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

void fz_read_string(fz_context *ctx, fz_stream *stm, char *buffer, int len)
{
	int c;
	do
	{
		if (len <= 0)
			fz_throw(ctx, FZ_ERROR_GENERIC, "Buffer overrun reading null terminated string");

		c = fz_read_byte(ctx, stm);
		if (c == EOF)
			fz_throw(ctx, FZ_ERROR_GENERIC, "EOF reading null terminated string");
		*buffer++ = c;
		len--;
	}
	while (c != 0);
}