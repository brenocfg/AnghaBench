#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_7__ {int bytewidth; int height; int width; int bytesPerPixel; int /*<<< orphan*/  imageBuffer; } ;
struct TYPE_6__ {int /*<<< orphan*/  red; int /*<<< orphan*/  green; int /*<<< orphan*/  blue; } ;
typedef  TYPE_1__ MMRGBColor ;
typedef  TYPE_2__* MMBitmapRef ;

/* Variables and functions */
 TYPE_1__* MMRGBColorRefAtPoint (TYPE_2__*,size_t,size_t) ; 
 scalar_t__ MMRGB_IS_BGR ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void copyBGRDataFromMMBitmap(MMBitmapRef bitmap, uint8_t *dest)
{
	if (MMRGB_IS_BGR && (bitmap->bytewidth % 4) == 0) { /* No conversion needed. */
		memcpy(dest, bitmap->imageBuffer, bitmap->bytewidth * bitmap->height);
	} else { /* Convert to RGB with other-than-4-byte alignment. */
		const size_t bytewidth = (bitmap->width * bitmap->bytesPerPixel + 3) & ~3;
		size_t y;

		/* Copy image data row by row. */
		for (y = 0; y < bitmap->height; ++y) {
			uint8_t *rowptr = dest + (y * bytewidth);
			size_t x;
			for (x = 0; x < bitmap->width; ++x) {
				MMRGBColor *color = MMRGBColorRefAtPoint(bitmap, x, y);

				/* BMP files are stored in BGR format. */
				rowptr[0] = color->blue;
				rowptr[1] = color->green;
				rowptr[2] = color->red;

				rowptr += bitmap->bytesPerPixel;
			}
		}
	}
}