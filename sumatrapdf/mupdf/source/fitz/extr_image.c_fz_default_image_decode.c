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
struct TYPE_3__ {int x1; int x0; int y1; int y0; } ;
typedef  TYPE_1__ fz_irect ;

/* Variables and functions */

void fz_default_image_decode(void *arg, int w, int h, int l2factor, fz_irect *subarea)
{
	(void)arg;

	if ((subarea->x1-subarea->x0)*(subarea->y1-subarea->y0) >= (w*h/10)*9)
	{
		/* Either no subarea specified, or a subarea 90% or more of the
		 * whole area specified. Use the whole image. */
		subarea->x0 = 0;
		subarea->y0 = 0;
		subarea->x1 = w;
		subarea->y1 = h;
	}
	else
	{
		/* Clip to the edges if they are within 1% */
		if (subarea->x0 <= w/100)
			subarea->x0 = 0;
		if (subarea->y0 <= h/100)
			subarea->y0 = 0;
		if (subarea->x1 >= w*99/100)
			subarea->x1 = w;
		if (subarea->y1 >= h*99/100)
			subarea->y1 = h;
	}
}