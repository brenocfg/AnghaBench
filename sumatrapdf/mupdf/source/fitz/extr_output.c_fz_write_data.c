#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int bp; int ep; int wp; int /*<<< orphan*/  state; int /*<<< orphan*/  (* write ) (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t) ;} ;
typedef  TYPE_1__ fz_output ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int,char const*,size_t) ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub2 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/  stub3 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  stub4 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char const*,size_t) ; 

void
fz_write_data(fz_context *ctx, fz_output *out, const void *data_, size_t size)
{
	const char *data = data_;

	if (out->bp)
	{
		if (size >= (size_t) (out->ep - out->bp)) /* too large for buffer */
		{
			if (out->wp > out->bp)
			{
				out->write(ctx, out->state, out->bp, out->wp - out->bp);
				out->wp = out->bp;
			}
			out->write(ctx, out->state, data, size);
		}
		else if (out->wp + size <= out->ep) /* fits in current buffer */
		{
			memcpy(out->wp, data, size);
			out->wp += size;
		}
		else /* fits if we flush first */
		{
			size_t n = out->ep - out->wp;
			memcpy(out->wp, data, n);
			out->write(ctx, out->state, out->bp, out->ep - out->bp);
			memcpy(out->bp, data + n, size - n);
			out->wp = out->bp + size - n;
		}
	}
	else
	{
		out->write(ctx, out->state, data, size);
	}
}