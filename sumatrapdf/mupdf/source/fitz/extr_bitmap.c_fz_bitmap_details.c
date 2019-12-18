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
struct TYPE_3__ {int w; int h; int n; int stride; } ;
typedef  TYPE_1__ fz_bitmap ;

/* Variables and functions */

void fz_bitmap_details(fz_bitmap *bit, int *w, int *h, int *n, int *stride)
{
	if (!bit)
	{
		if (w)
			*w = 0;
		if (h)
			*h = 0;
		if (n)
			*n = 0;
		if (stride)
			*stride = 0;
		return;
	}
	if (w)
		*w = bit->w;
	if (h)
		*h = bit->h;
	if (n)
		*n = bit->n;
	if (stride)
		*stride = bit->stride;
}