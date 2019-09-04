#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_5__ {size_t height; size_t bytewidth; int /*<<< orphan*/  bytesPerPixel; int /*<<< orphan*/  bitsPerPixel; int /*<<< orphan*/  width; int /*<<< orphan*/ * imageBuffer; } ;
typedef  TYPE_1__* MMBitmapRef ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 TYPE_1__* createMMBitmap (int /*<<< orphan*/ *,int /*<<< orphan*/ ,size_t,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * malloc (size_t const) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t const) ; 

MMBitmapRef copyMMBitmap(MMBitmapRef bitmap)
{
	uint8_t *copiedBuf = NULL;

	assert(bitmap != NULL);
	if (bitmap->imageBuffer != NULL) {
		const size_t bufsize = bitmap->height * bitmap->bytewidth;
		copiedBuf = malloc(bufsize);
		if (copiedBuf == NULL) return NULL;

		memcpy(copiedBuf, bitmap->imageBuffer, bufsize);
	}

	return createMMBitmap(copiedBuf,
	                      bitmap->width,
	                      bitmap->height,
	                      bitmap->bytewidth,
	                      bitmap->bitsPerPixel,
	                      bitmap->bytesPerPixel);
}