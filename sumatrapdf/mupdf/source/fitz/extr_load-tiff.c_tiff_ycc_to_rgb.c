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
struct tiff {int samplesperpixel; unsigned int imagelength; unsigned char* samples; unsigned int stride; unsigned int imagewidth; } ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 unsigned char fz_clampi (int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
tiff_ycc_to_rgb(fz_context *ctx, struct tiff *tiff)
{
	unsigned x, y;
	int offset = tiff->samplesperpixel;

	for (y = 0; y < tiff->imagelength; y++)
	{
		unsigned char * row = &tiff->samples[tiff->stride * y];
		for (x = 0; x < tiff->imagewidth; x++)
		{
			int ycc[3];
			ycc[0] = row[x * offset + 0];
			ycc[1] = row[x * offset + 1] - 128;
			ycc[2] = row[x * offset + 2] - 128;

			row[x * offset + 0] = fz_clampi(ycc[0] + 1.402f * ycc[2], 0, 255);
			row[x * offset + 1] = fz_clampi(ycc[0] - 0.34413f * ycc[1] - 0.71414f * ycc[2], 0, 255);
			row[x * offset + 2] = fz_clampi(ycc[0] + 1.772f * ycc[1], 0, 255);
		}
	}
}