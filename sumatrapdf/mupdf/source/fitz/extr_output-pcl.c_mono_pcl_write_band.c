#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int features; } ;
struct TYPE_4__ {int w; int yres; int /*<<< orphan*/ * out; } ;
struct TYPE_5__ {int num_blank_lines; unsigned char* prev; unsigned char* mode2buf; unsigned char* mode3buf; scalar_t__ top_of_page; TYPE_3__ options; TYPE_1__ super; } ;
typedef  TYPE_2__ mono_pcl_band_writer ;
typedef  TYPE_3__ fz_pcl_options ;
typedef  int /*<<< orphan*/  fz_output ;
typedef  int /*<<< orphan*/  fz_context ;
typedef  int /*<<< orphan*/  fz_band_writer ;

/* Variables and functions */
 int MIN_SKIP_LINES ; 
 int PCL3_SPACING ; 
 int PCL_ANY_SPACING ; 
 int PCL_MODE_2_COMPRESSION ; 
 int PCL_MODE_3_COMPRESSION ; 
 char* from2to3 ; 
 char* from3to2 ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char const*,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int /*<<< orphan*/ ,int) ; 
 int mode2compress (unsigned char*,unsigned char const*,int) ; 
 int mode3compress (unsigned char*,unsigned char const*,unsigned char*,int) ; 
 int penalty_from2to3 ; 
 int penalty_from3to2 ; 

__attribute__((used)) static void
mono_pcl_write_band(fz_context *ctx, fz_band_writer *writer_, int ss, int band_start, int band_height, const unsigned char *data)
{
	mono_pcl_band_writer *writer = (mono_pcl_band_writer *)writer_;
	fz_output *out = writer->super.out;
	int w = writer->super.w;
	int yres = writer->super.yres;
	const unsigned char *out_data;
	int y, rmask, line_size;
	int num_blank_lines;
	int compression = -1;
	unsigned char *prev = NULL;
	unsigned char *mode2buf = NULL;
	unsigned char *mode3buf = NULL;
	int out_count;
	const fz_pcl_options *pcl;

	if (!out)
		return;

	num_blank_lines = writer->num_blank_lines;
	rmask = ~0 << (-w & 7);
	line_size = (w + 7)/8;
	prev = writer->prev;
	mode2buf = writer->mode2buf;
	mode3buf = writer->mode3buf;
	pcl = &writer->options;

	/* Transfer raster graphics. */
	for (y = 0; y < band_height; y++, data += ss)
	{
		const unsigned char *end_data = data + line_size;

		if ((end_data[-1] & rmask) == 0)
		{
			end_data--;
			while (end_data > data && end_data[-1] == 0)
				end_data--;
		}
		if (end_data == data)
		{
			/* Blank line */
			num_blank_lines++;
			continue;
		}

		/* We've reached a non-blank line. */
		/* Put out a spacing command if necessary. */
		if (writer->top_of_page)
		{
			writer->top_of_page = 0;
			/* We're at the top of a page. */
			if (pcl->features & PCL_ANY_SPACING)
			{
				if (num_blank_lines > 0)
					fz_write_printf(ctx, out, "\033*p+%dY", num_blank_lines);
				/* Start raster graphics. */
				fz_write_string(ctx, out, "\033*r1A");
			}
			else if (pcl->features & PCL_MODE_3_COMPRESSION)
			{
				/* Start raster graphics. */
				fz_write_string(ctx, out, "\033*r1A");
				for (; num_blank_lines; num_blank_lines--)
					fz_write_string(ctx, out, "\033*b0W");
			}
			else
			{
				/* Start raster graphics. */
				fz_write_string(ctx, out, "\033*r1A");
				for (; num_blank_lines; num_blank_lines--)
					fz_write_string(ctx, out, "\033*bW");
			}
		}

		/* Skip blank lines if any */
		else if (num_blank_lines != 0)
		{
			/* Moving down from current position causes head
			 * motion on the DeskJet, so if the number of lines
			 * is small, we're better off printing blanks.
			 *
			 * For Canon LBP4i and some others, <ESC>*b<n>Y
			 * doesn't properly clear the seed row if we are in
			 * compression mode 3.
			 */
			if ((num_blank_lines < MIN_SKIP_LINES && compression != 3) ||
					!(pcl->features & PCL_ANY_SPACING))
			{
				int mode_3ns = ((pcl->features & PCL_MODE_3_COMPRESSION) && !(pcl->features & PCL_ANY_SPACING));
				if (mode_3ns && compression != 2)
				{
					/* Switch to mode 2 */
					fz_write_string(ctx, out, from3to2);
					compression = 2;
				}
				if (pcl->features & PCL_MODE_3_COMPRESSION)
				{
					/* Must clear the seed row. */
					fz_write_string(ctx, out, "\033*b1Y");
					num_blank_lines--;
				}
				if (mode_3ns)
				{
					for (; num_blank_lines; num_blank_lines--)
						fz_write_string(ctx, out, "\033*b0W");
				}
				else
				{
					for (; num_blank_lines; num_blank_lines--)
						fz_write_string(ctx, out, "\033*bW");
				}
			}
			else if (pcl->features & PCL3_SPACING)
				fz_write_printf(ctx, out, "\033*p+%dY", num_blank_lines * yres);
			else
				fz_write_printf(ctx, out, "\033*b%dY", num_blank_lines);
			/* Clear the seed row (only matters for mode 3 compression). */
			memset(prev, 0, line_size);
		}
		num_blank_lines = 0;

		/* Choose the best compression mode for this particular line. */
		if (pcl->features & PCL_MODE_3_COMPRESSION)
		{
			/* Compression modes 2 and 3 are both available. Try
			 * both and see which produces the least output data.
			 */
			int count3 = mode3compress(mode3buf, data, prev, line_size);
			int count2 = mode2compress(mode2buf, data, line_size);
			int penalty3 = (compression == 3 ? 0 : penalty_from2to3);
			int penalty2 = (compression == 2 ? 0 : penalty_from3to2);

			if (count3 + penalty3 < count2 + penalty2)
			{
				if (compression != 3)
					fz_write_string(ctx, out, from2to3);
				compression = 3;
				out_data = (unsigned char *)mode3buf;
				out_count = count3;
			}
			else
			{
				if (compression != 2)
					fz_write_string(ctx, out, from3to2);
				compression = 2;
				out_data = (unsigned char *)mode2buf;
				out_count = count2;
			}
		}
		else if (pcl->features & PCL_MODE_2_COMPRESSION)
		{
			out_data = mode2buf;
			out_count = mode2compress(mode2buf, data, line_size);
		}
		else
		{
			out_data = data;
			out_count = line_size;
		}

		/* Transfer the data */
		fz_write_printf(ctx, out, "\033*b%dW", out_count);
		fz_write_data(ctx, out, out_data, out_count);
	}

	writer->num_blank_lines = num_blank_lines;
}