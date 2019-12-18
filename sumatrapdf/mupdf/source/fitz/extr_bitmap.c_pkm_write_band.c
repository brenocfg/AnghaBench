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
struct TYPE_3__ {int w; int h; int n; int /*<<< orphan*/ * out; } ;
typedef  TYPE_1__ fz_band_writer ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  fz_write_data (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * pkm ; 

__attribute__((used)) static void
pkm_write_band(fz_context *ctx, fz_band_writer *writer, int stride, int band_start, int band_height, const unsigned char *p)
{
	fz_output *out = writer->out;
	int w = writer->w;
	int h = writer->h;
	int n = writer->n;
	int bytestride;
	int end = band_start + band_height;

	if (n != 4)
		fz_throw(ctx, FZ_ERROR_GENERIC, "wrong number of color components in bitmap");

	if (end > h)
		end = h;
	end -= band_start;

	bytestride = stride - (w>>1);
	while (end--)
	{
		int ww = w-1;
		while (ww > 0)
		{
			fz_write_data(ctx, out, &pkm[8 * *p++], 8);
			ww -= 2;
		}
		if (ww == 0)
			fz_write_data(ctx, out, &pkm[8 * *p], 4);
		p += bytestride;
	}
}