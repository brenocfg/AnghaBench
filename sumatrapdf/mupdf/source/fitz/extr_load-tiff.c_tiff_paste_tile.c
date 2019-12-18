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
struct tiff {unsigned int tilelength; unsigned int imagelength; unsigned int tilewidth; unsigned int imagewidth; unsigned int samplesperpixel; unsigned char* samples; unsigned int stride; unsigned int bitspersample; unsigned int tilestride; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void
tiff_paste_tile(fz_context *ctx, struct tiff *tiff, unsigned char *tile, unsigned int row, unsigned int col)
{
	unsigned int x, y, k;

	for (y = 0; y < tiff->tilelength && row + y < tiff->imagelength; y++)
	{
		for (x = 0; x < tiff->tilewidth && col + x < tiff->imagewidth; x++)
		{
			for (k = 0; k < tiff->samplesperpixel; k++)
			{
				unsigned char *dst, *src;

				dst = tiff->samples;
				dst += (row + y) * tiff->stride;
				dst += (((col + x) * tiff->samplesperpixel + k) * tiff->bitspersample + 7) / 8;

				src = tile;
				src += y * tiff->tilestride;
				src += ((x * tiff->samplesperpixel + k) * tiff->bitspersample + 7) / 8;

				switch (tiff->bitspersample)
				{
				case 1: *dst |= (*src >> (7 - 1 * ((col + x) % 8))) & 0x1; break;
				case 2: *dst |= (*src >> (6 - 2 * ((col + x) % 4))) & 0x3; break;
				case 4: *dst |= (*src >> (4 - 4 * ((col + x) % 2))) & 0xf; break;
				case 8: *dst = *src; break;
				case 16: dst[0] = src[0]; dst[1] = src[1]; break;
				case 24: dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; break;
				case 32: dst[0] = src[0]; dst[1] = src[1]; dst[2] = src[2]; dst[3] = src[3]; break;
				}
			}
		}
	}
}