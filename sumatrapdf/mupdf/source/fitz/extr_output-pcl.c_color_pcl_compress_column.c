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
struct TYPE_4__ {int /*<<< orphan*/ * out; } ;
struct TYPE_5__ {unsigned char* linebuf; unsigned char* compbuf; unsigned char* compbuf2; TYPE_1__ super; } ;
typedef  TYPE_2__ color_pcl_band_writer ;

/* Variables and functions */
 int delta_compression (unsigned char*,unsigned char*,unsigned char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  flush_if_not_room (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int*,int) ; 
 int /*<<< orphan*/  fz_mini (int,int) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int) ; 
 int /*<<< orphan*/  fz_write_printf (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  fz_write_string (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  line_is_blank (unsigned char*,unsigned char const*,int) ; 
 scalar_t__ memcmp (unsigned char const*,unsigned char const*,int) ; 
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static void
color_pcl_compress_column(fz_context *ctx, color_pcl_band_writer *writer, const unsigned char *sp, int w, int h, int stride)
{
	fz_output *out = writer->super.out;
	int ss = w * 3;
	int seed_valid = 0;
	int fill = 0;
	int y = 0;
	unsigned char *prev = writer->linebuf + w * 3;
	unsigned char *curr = writer->linebuf;
	unsigned char *comp = writer->compbuf;
	unsigned char *comp2 = writer->compbuf2;

	while (y < h)
	{
		/* Skip over multiple blank lines */
		int blanks;
		do
		{
			blanks = 0;
			while (blanks < 32767 && y < h)
			{
				if (!line_is_blank(curr, sp, w))
					break;
				blanks++;
				y++;
			}

			if (blanks)
			{
				flush_if_not_room(ctx, out, comp, &fill, 3);
				comp[fill++] = 4; /* Empty row */
				comp[fill++] = blanks>>8;
				comp[fill++] = blanks & 0xFF;
				seed_valid = 0;
			}
		}
		while (blanks == 32767);

		if (y == h)
			break;

		/* So, at least 1 more line to copy, and it's in curr */
		if (seed_valid && memcmp(curr, prev, ss) == 0)
		{
			int count = 1;
			sp += stride;
			y++;
			while (count < 32767 && y < h)
			{
				if (memcmp(sp-stride, sp, ss) != 0)
					break;
				count++;
				sp += stride;
				y++;
			}
			flush_if_not_room(ctx, out, comp, &fill, 3);
			comp[fill++] = 5; /* Duplicate row */
			comp[fill++] = count>>8;
			comp[fill++] = count & 0xFF;
		}
		else
		{
			unsigned char *tmp;
			int len = 0;

			/* Compress the line into our fixed buffer. */
			if (seed_valid)
				len = delta_compression(curr, prev, comp2, ss, fz_mini(ss-1, 32767-3));

			if (len > 0)
			{
				/* Delta compression */
				flush_if_not_room(ctx, out, comp, &fill, len+3);
				comp[fill++] = 3; /* Delta compression */
				comp[fill++] = len>>8;
				comp[fill++] = len & 0xFF;
				memcpy(&comp[fill], comp2, len);
				fill += len;
			}
			else
			{
				flush_if_not_room(ctx, out, comp, &fill, 3 + ss);

				/* PCL requires that all rows MUST fit in at most 1 block, so
				 * we are carefully sending columns that are only so wide. */

				/* Unencoded */
				/* Transfer Raster Data: ss+3 bytes, 0 = Unencoded, count high, count low */
				comp[fill++] = 0;
				comp[fill++] = ss>>8;
				comp[fill++] = ss & 0xFF;
				memcpy(&comp[fill], curr, ss);
				fill += ss;
				seed_valid = 1;
			}

			/* curr becomes prev */
			tmp = prev; prev = curr; curr = tmp;
			sp += stride;
			y++;
		}
	}
	/* And flush */
	if (fill) {
		fz_write_printf(ctx, out, "\033*b%dW", fill);
		fz_write_data(ctx, out, comp, fill);
	}

	/* End Raster Graphics */
	fz_write_string(ctx, out, "\033*rC");
}