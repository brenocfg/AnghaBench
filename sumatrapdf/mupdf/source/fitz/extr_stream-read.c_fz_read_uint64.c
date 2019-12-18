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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  fz_stream ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int EOF ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_read_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

uint64_t fz_read_uint64(fz_context *ctx, fz_stream *stm)
{
	int a = fz_read_byte(ctx, stm);
	int b = fz_read_byte(ctx, stm);
	int c = fz_read_byte(ctx, stm);
	int d = fz_read_byte(ctx, stm);
	int e = fz_read_byte(ctx, stm);
	int f = fz_read_byte(ctx, stm);
	int g = fz_read_byte(ctx, stm);
	int h = fz_read_byte(ctx, stm);
	if (a == EOF || b == EOF || c == EOF || d == EOF || e == EOF || f == EOF || g == EOF || h == EOF)
		fz_throw(ctx, FZ_ERROR_GENERIC, "premature end of file in int64");
	return ((uint64_t)a<<56) | ((uint64_t)b<<48) | ((uint64_t)c<<40) | ((uint64_t)d<<32)
		| ((uint64_t)e<<24) | ((uint64_t)f<<16) | ((uint64_t)g<<8) | ((uint64_t)h);
}