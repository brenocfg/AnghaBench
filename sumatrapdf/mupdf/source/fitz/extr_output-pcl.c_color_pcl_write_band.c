#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;
struct TYPE_4__ {int w; int h; int xres; int /*<<< orphan*/ * out; } ;
struct TYPE_5__ {TYPE_1__ super; } ;
typedef  TYPE_2__ color_pcl_band_writer ;

/* Variables and functions */
 int /*<<< orphan*/  color_pcl_compress_column (int /*<<< orphan*/ *,TYPE_2__*,unsigned char const*,int,int,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int,...) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
color_pcl_write_band(fz_context *ctx, fz_band_writer *writer_, int stride, int band_start, int band_height, const unsigned char *sp)
{
	color_pcl_band_writer *writer = (color_pcl_band_writer *)writer_;
	fz_output *out = writer->super.out;
	int w = writer->super.w;
	int h = writer->super.h;
	int xres = writer->super.xres;
	int cw;
	int x;

	if (!out)
		return;

	if (band_start+band_height >= h)
		band_height = h - band_start;

	/* We have to specify image output size in decipoints (720dpi).
	 * Most usual PCL resolutions are a multiple of 75.
	 * Pick our maximum column size to be 10800 = 15*720 = 144*75
	 * to give us good results. 10800 * 3 = 32400 < 32760 */
	cw = 10800; /* Limited by how much rowdata we can send at once */
	if (cw > w)
		cw = w;

	for (x = 0; x*cw < w; x++)
	{
		int col_w = w - cw*x;
		if (col_w > cw)
			col_w = cw;

		/* Top left corner */
		fz_write_printf(ctx, out, "\033*p%dx%dY", x*cw, band_start);

		/* Raster height */
		fz_write_printf(ctx, out, "\033*r%dT", band_height);

		/* Raster width */
		fz_write_printf(ctx, out, "\033*r%dS", col_w);

		/* Destination height */
		fz_write_printf(ctx, out, "\033*t%dV", band_height*720/xres);

		/* Destination width */
		fz_write_printf(ctx, out, "\033*t%dH", col_w*720/xres);

		/* start raster graphics */
		/* 1 = start at cursor position */
		fz_write_string(ctx, out, "\033*r3A");

		/* Now output the actual bitmap */
		/* Adaptive Compression */
		fz_write_string(ctx, out, "\033*b5M");

		color_pcl_compress_column(ctx, writer, sp + x * cw * 3, col_w, band_height, stride);
	}
}