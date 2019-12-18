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
struct tiff {int bitspersample; int samplesperpixel; unsigned int colormaplen; int imagelength; int imagewidth; unsigned char* samples; unsigned int stride; int* colormap; scalar_t__ extrasamples; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int UINT_MAX ; 
 int /*<<< orphan*/  fz_free (int /*<<< orphan*/ *,unsigned char*) ; 
 unsigned char* fz_malloc (int /*<<< orphan*/ *,unsigned int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int tiff_getcomp (unsigned char*,unsigned int,int) ; 

__attribute__((used)) static void
tiff_expand_colormap(fz_context *ctx, struct tiff *tiff)
{
	int maxval = 1 << tiff->bitspersample;
	unsigned char *samples;
	unsigned char *src, *dst;
	unsigned int x, y;
	unsigned int stride;

	/* colormap has first all red, then all green, then all blue values */
	/* colormap values are 0..65535, bits is 4 or 8 */
	/* image can be with or without extrasamples: comps is 1 or 2 */

	if (tiff->samplesperpixel != 1 && tiff->samplesperpixel != 2)
		fz_throw(ctx, FZ_ERROR_GENERIC, "invalid number of samples for RGBPal");

	if (tiff->bitspersample != 1 && tiff->bitspersample != 2 && tiff->bitspersample != 4 && tiff->bitspersample != 8 && tiff->bitspersample != 16)
		fz_throw(ctx, FZ_ERROR_GENERIC, "invalid number of bits for RGBPal");

	if (tiff->colormaplen < (unsigned)maxval * 3)
		fz_throw(ctx, FZ_ERROR_GENERIC, "insufficient colormap data");

	if (tiff->imagelength > UINT_MAX / tiff->imagewidth / (tiff->samplesperpixel + 2))
		fz_throw(ctx, FZ_ERROR_GENERIC, "image too large");

	stride = tiff->imagewidth * (tiff->samplesperpixel + 2);

	samples = fz_malloc(ctx, stride * tiff->imagelength);

	for (y = 0; y < tiff->imagelength; y++)
	{
		src = tiff->samples + (unsigned int)(tiff->stride * y);
		dst = samples + (unsigned int)(stride * y);

		for (x = 0; x < tiff->imagewidth; x++)
		{
			if (tiff->extrasamples)
			{
				int c = tiff_getcomp(src, x * 2, tiff->bitspersample);
				int a = tiff_getcomp(src, x * 2 + 1, tiff->bitspersample);
				*dst++ = tiff->colormap[c + 0] >> 8;
				*dst++ = tiff->colormap[c + maxval] >> 8;
				*dst++ = tiff->colormap[c + maxval * 2] >> 8;
				if (tiff->bitspersample <= 8)
					*dst++ = a << (8 - tiff->bitspersample);
				else
					*dst++ = a >> (tiff->bitspersample - 8);
			}
			else
			{
				int c = tiff_getcomp(src, x, tiff->bitspersample);
				*dst++ = tiff->colormap[c + 0] >> 8;
				*dst++ = tiff->colormap[c + maxval] >> 8;
				*dst++ = tiff->colormap[c + maxval * 2] >> 8;
			}
		}
	}

	tiff->samplesperpixel += 2;
	tiff->bitspersample = 8;
	tiff->stride = stride;
	fz_free(ctx, tiff->samples);
	tiff->samples = samples;
}