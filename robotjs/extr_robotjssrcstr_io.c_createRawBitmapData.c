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
struct TYPE_7__ {int width; int height; } ;
struct TYPE_6__ {int /*<<< orphan*/  red; int /*<<< orphan*/  green; int /*<<< orphan*/  blue; } ;
typedef  TYPE_1__ MMRGBColor ;
typedef  TYPE_2__* MMBitmapRef ;

/* Variables and functions */
 TYPE_1__* MMRGBColorRefAtPoint (TYPE_2__*,size_t,size_t) ; 
 size_t STR_BYTES_PER_PIXEL ; 
 int /*<<< orphan*/ * calloc (size_t,int) ; 

__attribute__((used)) static uint8_t *createRawBitmapData(MMBitmapRef bitmap)
{
	uint8_t *raw = calloc(STR_BYTES_PER_PIXEL, bitmap->width * bitmap->height);
	size_t y;

	for (y = 0; y < bitmap->height; ++y) {
		/* No padding is added to string bitmaps. */
		const size_t rowOffset = y * bitmap->width * STR_BYTES_PER_PIXEL;
		size_t x;
		for (x = 0; x < bitmap->width; ++x) {
			/* Copy in BGR format. */
			const size_t colOffset = x * STR_BYTES_PER_PIXEL;
			uint8_t *dest = raw + rowOffset + colOffset;
			MMRGBColor *srcColor = MMRGBColorRefAtPoint(bitmap, x, y);
			dest[0] = srcColor->blue;
			dest[1] = srcColor->green;
			dest[2] = srcColor->red;
		}
	}

	return raw;
}