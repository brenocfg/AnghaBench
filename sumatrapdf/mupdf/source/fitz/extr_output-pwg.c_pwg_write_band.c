#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int w; int h; int n; int /*<<< orphan*/ * out; } ;
struct TYPE_4__ {TYPE_1__ super; } ;
typedef  TYPE_2__ pwg_band_writer ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fz_write_byte (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,int) ; 

__attribute__((used)) static void
pwg_write_band(fz_context *ctx, fz_band_writer *writer_, int stride, int band_start, int band_height, const unsigned char *samples)
{
	pwg_band_writer *writer = (pwg_band_writer *)writer_;
	fz_output *out = writer->super.out;
	int w = writer->super.w;
	int h = writer->super.h;
	const unsigned char *sp = samples;
	int n = writer->super.n;
	int ss = w * n;
	int y, x;

	/* Now output the actual bitmap, using a packbits like compression */
	y = 0;
	while (y < h)
	{
		int yrep;

		assert(sp == samples + y * stride);

		/* Count the number of times this line is repeated */
		for (yrep = 1; yrep < 256 && y+yrep < h; yrep++)
		{
			if (memcmp(sp, sp + yrep * stride, ss) != 0)
				break;
		}
		fz_write_byte(ctx, out, yrep-1);

		/* Encode the line */
		x = 0;
		while (x < w)
		{
			int d;

			assert(sp == samples + y * stride + x * n);

			/* How far do we have to look to find a repeated value? */
			for (d = 1; d < 128 && x+d < w; d++)
			{
				if (memcmp(sp + (d-1)*n, sp + d*n, n) == 0)
					break;
			}
			if (d == 1)
			{
				int xrep;

				/* We immediately have a repeat (or we've hit
				 * the end of the line). Count the number of
				 * times this value is repeated. */
				for (xrep = 1; xrep < 128 && x+xrep < w; xrep++)
				{
					if (memcmp(sp, sp + xrep*n, n) != 0)
						break;
				}
				fz_write_byte(ctx, out, xrep-1);
				fz_write_data(ctx, out, sp, n);
				sp += n*xrep;
				x += xrep;
			}
			else
			{
				fz_write_byte(ctx, out, 257-d);
				x += d;
				while (d > 0)
				{
					fz_write_data(ctx, out, sp, n);
					sp += n;
					d--;
				}
			}
		}

		/* Move to the next line */
		sp += stride*(yrep-1);
		y += yrep;
	}
}