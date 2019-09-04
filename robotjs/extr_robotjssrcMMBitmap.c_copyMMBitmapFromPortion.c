#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_14__ {size_t bytewidth; size_t bytesPerPixel; size_t const height; int /*<<< orphan*/  bitsPerPixel; int /*<<< orphan*/ * imageBuffer; } ;
struct TYPE_12__ {size_t height; int /*<<< orphan*/  width; } ;
struct TYPE_11__ {size_t y; size_t x; } ;
struct TYPE_13__ {TYPE_2__ size; TYPE_1__ origin; } ;
typedef  TYPE_3__ MMRect ;
typedef  TYPE_4__* MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  MMBitmapRectInBounds (TYPE_4__*,TYPE_3__) ; 
 int /*<<< orphan*/  assert (int) ; 
 TYPE_4__* createMMBitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t const,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/ * malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 

MMBitmapRef copyMMBitmapFromPortion(MMBitmapRef source, MMRect rect)
{
	assert(source != NULL);

	if (source->imageBuffer == NULL || !MMBitmapRectInBounds(source, rect)) {
		return NULL;
	} else {
		uint8_t *copiedBuf = NULL;
		const size_t bufsize = rect.size.height * source->bytewidth;
		const size_t offset = (source->bytewidth * rect.origin.y) +
		                      (rect.origin.x * source->bytesPerPixel);

		/* Don't go over the bounds, programmer! */
		assert((bufsize + offset) <= (source->bytewidth * source->height));

		copiedBuf = malloc(bufsize);
		if (copiedBuf == NULL) return NULL;

		memcpy(copiedBuf, source->imageBuffer + offset, bufsize);

		return createMMBitmap(copiedBuf,
		                      rect.size.width,
		                      rect.size.height,
		                      source->bytewidth,
		                      source->bitsPerPixel,
		                      source->bytesPerPixel);
	}
}