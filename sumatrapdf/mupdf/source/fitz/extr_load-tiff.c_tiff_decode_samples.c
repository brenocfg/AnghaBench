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
struct tiff {int imagelength; int stride; unsigned char* samples; int compression; int predictor; int imagewidth; int samplesperpixel; int bitspersample; int photometric; int extrasamples; scalar_t__ order; scalar_t__ colormap; scalar_t__ stripbytecounts; scalar_t__ stripoffsets; scalar_t__ rowsperstrip; scalar_t__ tilebytecounts; scalar_t__ tileoffsets; scalar_t__ tilewidth; scalar_t__ tilelength; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int /*<<< orphan*/  FZ_ERROR_MEMORY ; 
 scalar_t__ TII ; 
 int UINT_MAX ; 
 unsigned char* fz_malloc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  tiff_decode_strips (int /*<<< orphan*/ *,struct tiff*) ; 
 int /*<<< orphan*/  tiff_decode_tiles (int /*<<< orphan*/ *,struct tiff*) ; 
 int /*<<< orphan*/  tiff_expand_colormap (int /*<<< orphan*/ *,struct tiff*) ; 
 int /*<<< orphan*/  tiff_invert_line (unsigned char*,int,int,int,int) ; 
 int /*<<< orphan*/  tiff_scale_lab_samples (int /*<<< orphan*/ *,unsigned char*,int,int) ; 
 int /*<<< orphan*/  tiff_swap_byte_order (unsigned char*,int) ; 
 int /*<<< orphan*/  tiff_unpredict_line (unsigned char*,int,int,int) ; 
 int /*<<< orphan*/  tiff_ycc_to_rgb (int /*<<< orphan*/ *,struct tiff*) ; 

__attribute__((used)) static void
tiff_decode_samples(fz_context *ctx, struct tiff *tiff)
{
	unsigned i;

	if (tiff->imagelength > UINT_MAX / tiff->stride)
		fz_throw(ctx, FZ_ERROR_MEMORY, "image too large");
	tiff->samples = fz_malloc(ctx, tiff->imagelength * tiff->stride);
	memset(tiff->samples, 0x55, tiff->imagelength * tiff->stride);

	if (tiff->tilelength && tiff->tilewidth && tiff->tileoffsets && tiff->tilebytecounts)
		tiff_decode_tiles(ctx, tiff);
	else if (tiff->rowsperstrip && tiff->stripoffsets && tiff->stripbytecounts)
		tiff_decode_strips(ctx, tiff);
	else
		fz_throw(ctx, FZ_ERROR_GENERIC, "image is missing both strip and tile data");

	/* Predictor (only for LZW and Flate) */
	if ((tiff->compression == 5 || tiff->compression == 8 || tiff->compression == 32946) && tiff->predictor == 2)
	{
		unsigned char *p = tiff->samples;
		for (i = 0; i < tiff->imagelength; i++)
		{
			tiff_unpredict_line(p, tiff->imagewidth, tiff->samplesperpixel, tiff->bitspersample);
			p += tiff->stride;
		}
	}

	/* YCbCr -> RGB, but JPEG already has done this conversion  */
	if (tiff->photometric == 6 && tiff->compression != 6 && tiff->compression != 7)
		tiff_ycc_to_rgb(ctx, tiff);

	/* RGBPal */
	if (tiff->photometric == 3 && tiff->colormap)
		tiff_expand_colormap(ctx, tiff);

	/* WhiteIsZero .. invert */
	if (tiff->photometric == 0)
	{
		unsigned char *p = tiff->samples;
		for (i = 0; i < tiff->imagelength; i++)
		{
			tiff_invert_line(p, tiff->imagewidth, tiff->samplesperpixel, tiff->bitspersample, tiff->extrasamples);
			p += tiff->stride;
		}
	}

	/* Premultiplied transparency */
	if (tiff->extrasamples == 1)
	{
		/* In GhostXPS we undo the premultiplication here; muxps holds
		 * all our images premultiplied by default, so nothing to do.
		 */
	}

	/* Non-premultiplied transparency */
	if (tiff->extrasamples == 2)
	{
		/* Premultiplied files are corrected for elsewhere */
	}

	/* Byte swap 16-bit images to big endian if necessary */
	if (tiff->bitspersample == 16 && tiff->order == TII)
		tiff_swap_byte_order(tiff->samples, tiff->imagewidth * tiff->imagelength * tiff->samplesperpixel);

	/* Lab colorspace expects all sample components 0..255.
	TIFF supplies them as L = 0..255, a/b = -128..127 (for
	8 bits per sample, -32768..32767 for 16 bits per sample)
	Scale them to the colorspace's expectations. */
	if (tiff->photometric == 8 && tiff->samplesperpixel == 3)
		tiff_scale_lab_samples(ctx, tiff->samples, tiff->bitspersample, tiff->imagewidth * tiff->imagelength);
}