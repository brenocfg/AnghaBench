#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
struct TYPE_2__ {size_t blue; size_t green; size_t red; } ;
typedef  TYPE_1__ MMRGBColor ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 scalar_t__ MMRGB_IS_BGR ; 
 int /*<<< orphan*/  assert (int) ; 
 size_t* calloc (int,size_t) ; 
 scalar_t__ fread (size_t*,size_t const,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (size_t*) ; 
 size_t* malloc (size_t) ; 

__attribute__((used)) static uint8_t *readImageData(FILE *fp, size_t width, size_t height,
                              uint8_t bytesPerPixel, size_t bytewidth)
{
	size_t imageSize = bytewidth * height;
	uint8_t *imageBuf = calloc(1, imageSize);

	if (MMRGB_IS_BGR && (bytewidth % 4) == 0) { /* No conversion needed. */
		if (fread(imageBuf, imageSize, 1, fp) == 0) {
			free(imageBuf);
			return NULL;
		}
	} else { /* Convert from BGR with 4-byte alignment. */
		uint8_t *row = malloc(bytewidth);
		size_t y;
		const size_t bmp_bytewidth = (width * bytesPerPixel + 3) & ~3;

		if (row == NULL) return NULL;
		assert(bmp_bytewidth <= bytewidth);

		/* Read image data row by row. */
		for (y = 0; y < height; ++y) {
			const size_t rowOffset = y * bytewidth;
			size_t x;
			uint8_t *rowptr = row;
			if (fread(row, bmp_bytewidth, 1, fp) == 0) {
				free(imageBuf);
				free(row);
				return NULL;
			}

			for (x = 0; x < width; ++x) {
				const size_t colOffset = x * bytesPerPixel;
				MMRGBColor *color = (MMRGBColor *)(imageBuf +
				                                   rowOffset + colOffset);

				/* BMP files are stored in BGR format. */
				color->blue = rowptr[0];
				color->green = rowptr[1];
				color->red = rowptr[2];
				rowptr += bytesPerPixel;
			}
		}

		free(row);
	}

	return imageBuf;
}