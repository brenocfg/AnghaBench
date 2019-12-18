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
struct tiff {int samplesperpixel; int bitspersample; unsigned int imagewidth; unsigned int imagelength; unsigned int* ycbcrsubsamp; unsigned int stride; unsigned char* samples; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  fz_is_pow2 (unsigned int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,unsigned int,unsigned int) ; 

__attribute__((used)) static void
tiff_paste_subsampled_tile(fz_context *ctx, struct tiff *tiff, unsigned char *tile, unsigned len, unsigned tw, unsigned th, unsigned col, unsigned row)
{
	/*
	This explains how the samples are laid out in tiff data, the spec example is non-obvious.
	The y, cb, cr indicies follow the spec, i.e. y17 is the y sample at row 1, column 7.
	All indicies start at 0.

	hexlookup = (horizontalsubsampling & 0xf) << 4 | (verticalsubsampling & 0xf)

	0x11	y00 cb00 cr00	0x21	y00 y01 cb00 cr00	0x41	y00 y01 y02 y03 cb00 cr00
		y01 cb01 cr01		y10 y11 cb01 cr01		y04 y05 y06 y07 cb01 cr01
		....			...				...
		y10 cb10 cr10		y20 y21 cb10 cr10		y10 y11 y12 y13 cb10 cr10
		y11 cb11 cr11		y30 y31 cb11 cr11		y14 y15 y16 y17 cb11 cr11

	0x12	y00		0x22	y00 y01			0x42	y00 y01 y02 y03
		y10 cb00 cr00		y10 y11 cb00 cr00		y10 y11 y12 y13 cb00 cr00
		y01			y02 y03				y04 y05 y06 y07
		y11 cb01 cr01		y12 y13 cb01 cr01		y14 y15 y16 y17 cb01 cr01
		....			...				...
		y20			y20 y21				y20 y21 y22 y23
		y30 cb10 cr10		y30 y31 cb10 cr10		y30 y31 y32 y33 cb10 cr10
		y21			y22 y23				y24 y25 y26 y27
		y31 cb11 cr11		y32 y33 cb11 cr11		y34 y35 y36 y37 cb11 cr11

	0x14	y00		0x24	y00 y01			0x44	y00 y01 y02 y03
		y10			y10 y11				y10 y11 y12 y13
		y20			y20 y21				y20 y21 y22 y23
		y30 cb00 cr00		y30 y31 cb00 cr00		y30 y31 y32 y33 cb00 cr00
		y01			y02 y03				y04 y05 y06 y07
		y11			y12 y13				y14 y15 y16 y17
		y21			y22 y23				y24 y25 y26 y27
		y31 cb01 cr01		y32 y33 cb01 cr01		y34 y35 y36 y37 cb01 cr01
		....			...				...
		y40			y40 y41				y40 y41 y42 y43
		y50			y50 y51				y50 y51 y52 y53
		y60			y60 y61				y60 y61 y62 y63
		y70 cb10 cr10		y70 y71 cb10 cr10		y70 y71 y72 y73 cb10 cr10
		y41			y42 y43				y44 y45 y46 y47
		y51			y52 y53				y54 y55 y56 y57
		y61			y62 y63				y64 y65 y66 y67
		y71 cb11 cr11		y72 y73 cb11 cr11		y74 y75 y76 y77 cb11 cr11
	*/

	unsigned char *src = tile;
	unsigned char *dst;
	unsigned x, y, w, h; /* coordinates and dimensions of entire image */
	unsigned sx, sy, sw, sh; /* coordinates and dimensions of a single subsample region, i.e. max 4 x 4 samples */
	int k;
	int offsets[4 * 4 * 3]; /* for a pixel position, these point to all pixel components in a subsample region */
	int *offset = offsets;

	assert(tiff->samplesperpixel == 3);
	assert(tiff->bitspersample == 8);

	w = tiff->imagewidth;
	h = tiff->imagelength;

	sx = 0;
	sy = 0;
	sw = tiff->ycbcrsubsamp[0];
	sh = tiff->ycbcrsubsamp[1];
	if (sw > 4 || sh > 4 || !fz_is_pow2(sw) || !fz_is_pow2(sh))
		fz_throw(ctx, FZ_ERROR_GENERIC, "Illegal TIFF Subsample values %d %d", sw, sh);

	for (k = 0; k < 3; k++)
		for (y = 0; y < sh; y++)
			for (x = 0; x < sw; x++)
				*offset++ = k + y * tiff->stride + x * 3;

	offset = offsets;
	x = col;
	y = row;
	k = 0;

	dst = &tiff->samples[row * tiff->stride + col * 3];

	while (src < tile + len)
	{
		if (k == 0)
		{ /* put all Y samples for a subsample region at the correct image pixel */
			if (y + sy < h && y + sy < row + th && x + sx < w && x + sx < col + tw)
				dst[*offset] = *src;
			offset++;

			if (++sx >= sw)
			{
				sx = 0;
				if (++sy >= sh)
				{
					sy = 0;
					k++;
				}
			}
		}
		else
		{ /* put all Cb/Cr samples for a subsample region at the correct image pixel */
			for (sy = 0; sy < sh; sy++)
				for (sx = 0; sx < sw; sx++)
				{
					if (y + sy < h && y + sy < row + th && x + sx < w && x + sx < col + tw)
						dst[*offset] = *src;
					offset++;
				}

			if (++k >= 3)
			{ /* we're done with this subsample region, on to the next one */
				k = sx = sy = 0;
				offset = offsets;

				dst += sw * 3;

				x += sw;
				if (x >= col + tw)
				{
					dst -= (x - (col + tw)) * 3;
					dst += (sh - 1) * w * 3;
					dst += col * 3;
					x = col;
					y += sh;
				}
			}
		}

		src++;
	}
}