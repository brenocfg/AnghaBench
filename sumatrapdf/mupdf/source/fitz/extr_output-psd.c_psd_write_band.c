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
struct TYPE_3__ {int w; int h; int n; scalar_t__ alpha; int /*<<< orphan*/ * out; } ;
struct TYPE_4__ {int num_additive; TYPE_1__ super; } ;
typedef  TYPE_2__ psd_band_writer ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  SEEK_CUR ; 
 int /*<<< orphan*/  fz_seek_output (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  psd_invert_buffer (unsigned char*,int) ; 

__attribute__((used)) static void
psd_write_band(fz_context *ctx, fz_band_writer *writer_, int stride, int band_start, int band_height, const unsigned char *sp)
{
	psd_band_writer *writer = (psd_band_writer *)(void *)writer_;
	fz_output *out = writer->super.out;
	int y, x, k, finalband;
	int w, h, n;
	unsigned char buffer[256];
	unsigned char *buffer_end = &buffer[sizeof(buffer)];
	unsigned char *b;
	int plane_inc;
	int line_skip;
	int num_additive = writer->num_additive;

	if (!out)
		return;

	w = writer->super.w;
	h = writer->super.h;
	n = writer->super.n;

	finalband = (band_start+band_height >= h);
	if (finalband)
		band_height = h - band_start;

	plane_inc = w * (h - band_height);
	line_skip = stride - w*n;
	b = buffer;
	if (writer->super.alpha)
	{
		const unsigned char *ap = &sp[n-1];
		for (k = 0; k < n-1; k++)
		{
			for (y = 0; y < band_height; y++)
			{
				for (x = 0; x < w; x++)
				{
					int a = *ap;
					ap += n;
					*b++ = a != 0 ? (*sp * 255 + 128)/a : 0;
					sp += n;
					if (b == buffer_end)
					{
						if (k >= num_additive)
							psd_invert_buffer(buffer, sizeof(buffer));
						fz_write_data(ctx, out, buffer, sizeof(buffer));
						b = buffer;
					}
				}
				sp += line_skip;
				ap += line_skip;
			}
			sp -= stride * band_height - 1;
			ap -= stride * band_height;
			if (b != buffer)
			{
				if (k >= num_additive)
					psd_invert_buffer(buffer, sizeof(buffer));
				fz_write_data(ctx, out, buffer, b - buffer);
				b = buffer;
			}
			fz_seek_output(ctx, out, plane_inc, SEEK_CUR);
		}
		for (y = 0; y < band_height; y++)
		{
			for (x = 0; x < w; x++)
			{
				*b++ = *sp;
				sp += n;
				if (b == buffer_end)
				{
					fz_write_data(ctx, out, buffer, sizeof(buffer));
					b = buffer;
				}
			}
			sp += line_skip;
		}
		if (b != buffer)
		{
			fz_write_data(ctx, out, buffer, b - buffer);
			b = buffer;
		}
		fz_seek_output(ctx, out, plane_inc, SEEK_CUR);
	}
	else
	{
		for (k = 0; k < n; k++)
		{
			for (y = 0; y < band_height; y++)
			{
				for (x = 0; x < w; x++)
				{
					*b++ = *sp;
					sp += n;
					if (b == buffer_end)
					{
						if (k >= num_additive)
							psd_invert_buffer(buffer, sizeof(buffer));
						fz_write_data(ctx, out, buffer, sizeof(buffer));
						b = buffer;
					}
				}
				sp += line_skip;
			}
			sp -= stride * band_height - 1;
			if (b != buffer)
			{
				if (k >= num_additive)
					psd_invert_buffer(buffer, sizeof(buffer));
				fz_write_data(ctx, out, buffer, b - buffer);
				b = buffer;
			}
			fz_seek_output(ctx, out, plane_inc, SEEK_CUR);
		}
	}
	fz_seek_output(ctx, out, w * (band_height - h * n), SEEK_CUR);
}