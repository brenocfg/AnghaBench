#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int width; int height; int stride; int const* data; } ;
typedef  TYPE_1__ Jbig2Image ;

/* Variables and functions */

int
jbig2_image_get_pixel(Jbig2Image *image, int x, int y)
{
    const int w = image->width;
    const int h = image->height;
    const int byte = (x >> 3) + y * image->stride;
    const int bit = 7 - (x & 7);

    if ((x < 0) || (x >= w))
        return 0;
    if ((y < 0) || (y >= h))
        return 0;

    return ((image->data[byte] >> bit) & 1);
}