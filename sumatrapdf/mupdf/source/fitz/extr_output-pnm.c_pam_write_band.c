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
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_3__ {int w; int h; int n; int alpha; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ fz_band_writer ;
typedef  int /*<<< orphan*/  buffer ;

/* Variables and functions */
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,...) ; 

__attribute__((used)) static void
pam_write_band(fz_context *ctx, fz_band_writer *writer, int stride, int band_start, int band_height, const unsigned char *sp)
{
	fz_output *out = writer->out;
	int w = writer->w;
	int h = writer->h;
	int n = writer->n;
	int alpha = writer->alpha;
	int x, y;
	int end = band_start + band_height;

	if (!out)
		return;

	if (end > h)
		end = h;
	end -= band_start;

	if (alpha)
	{
		/* Buffer must be a multiple of 2, 3 and 5 at least. */
		/* Also, for the generic case, it must be bigger than FZ_MAX_COLORS */
		char buffer[2*3*4*5*6];
		char *b = buffer;
		stride -= n * w;
		switch (n)
		{
		case 2:
			for (y = 0; y < end; y++)
			{
				for (x = 0; x < w; x++)
				{
					int a = sp[1];
					*b++ = a ? (sp[0] * 255 + (a>>1))/a : 0;
					*b++ = a;
					sp += 2;
					if (b == &buffer[sizeof(buffer)])
					{
						fz_write_data(ctx, out, buffer, sizeof(buffer));
						b = buffer;
					}
				}
				sp += stride;
			}
			if (b != buffer)
				fz_write_data(ctx, out, buffer, b - buffer);
			break;
		case 4:
			for (y = 0; y < end; y++)
			{
				for (x = 0; x < w; x++)
				{
					int a = sp[3];
					int inva = a ? 256 * 255 / a : 0;
					*b++ = (sp[0] * inva + 128)>>8;
					*b++ = (sp[1] * inva + 128)>>8;
					*b++ = (sp[2] * inva + 128)>>8;
					*b++ = a;
					sp += 4;
					if (b == &buffer[sizeof(buffer)])
					{
						fz_write_data(ctx, out, buffer, sizeof(buffer));
						b = buffer;
					}
				}
				sp += stride;
			}
			if (b != buffer)
				fz_write_data(ctx, out, buffer, b - buffer);
			break;
		case 5:
			for (y = 0; y < end; y++)
			{
				for (x = 0; x < w; x++)
				{
					int a = sp[4];
					int inva = a ? 256 * 255 / a : 0;
					*b++ = (sp[0] * inva + 128)>>8;
					*b++ = (sp[1] * inva + 128)>>8;
					*b++ = (sp[2] * inva + 128)>>8;
					*b++ = (sp[3] * inva + 128)>>8;
					*b++ = a;
					sp += 5;
					if (b == &buffer[sizeof(buffer)])
					{
						fz_write_data(ctx, out, buffer, sizeof(buffer));
						b = buffer;
					}
				}
				sp += stride;
			}
			if (b != buffer)
				fz_write_data(ctx, out, buffer, b - buffer);
			break;
		default:
			for (y = 0; y < end; y++)
			{
				for (x = 0; x < w; x++)
				{
					int a = sp[n-1];
					int inva = a ? 256 * 255 / a : 0;
					int k;
					for (k = 0; k < n-1; k++)
						*b++ = (*sp++ * inva + 128)>>8;
					*b++ = a;
					sp++;
					if (b >= &buffer[sizeof(buffer)] - n)
					{
						fz_write_data(ctx, out, buffer, b - buffer);
						b = buffer;
					}
				}
				sp += stride;
			}
			if (b != buffer)
				fz_write_data(ctx, out, buffer, b - buffer);
			break;
		}
	}
	else
		for (y = 0; y < end; y++)
		{
			fz_write_data(ctx, out, sp, w * n);
			sp += stride;
		}
}