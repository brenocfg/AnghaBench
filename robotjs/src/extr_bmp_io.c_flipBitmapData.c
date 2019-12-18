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

/* Variables and functions */
 int /*<<< orphan*/  free (void*) ; 
 void* malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (void*,void*,size_t) ; 

void flipBitmapData(void *data, size_t width, size_t height, size_t bytewidth)
{
	size_t top, bottom;
	void *topP;
	void *bottomP;
	void *tempbuf;

	if (height <= 1) return; /* No flipping necessary if height is <= 1. */

	top = 0;
	bottom = height - 1;
	tempbuf = malloc(bytewidth);
	if (tempbuf == NULL) return;

	while (top < bottom) {
		topP = (void *)((top * bytewidth) + (intptr_t)data);
		bottomP = (void *)((bottom * bytewidth) + (intptr_t)data);

		/* Save and swap scanlines.
		 * Does a simple in-place exchange with a temp buffer. */
		memcpy(tempbuf, topP, bytewidth);
		memcpy(topP, bottomP, bytewidth);
		memcpy(bottomP, tempbuf, bytewidth);

		++top;
		--bottom;
	}
	free(tempbuf);
}