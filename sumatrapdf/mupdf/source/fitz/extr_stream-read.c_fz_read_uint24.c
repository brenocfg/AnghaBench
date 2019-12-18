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
typedef  int uint32_t ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

uint32_t fz_read_uint24(fz_context *ctx, fz_stream *stm)
{
	int a = fz_read_byte(ctx, stm);
	int b = fz_read_byte(ctx, stm);
	int c = fz_read_byte(ctx, stm);
	if (a == EOF || b == EOF || c == EOF)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of file in int24");
	return ((uint32_t)a<<16) | ((uint32_t)b<<8) | ((uint32_t)c);
}