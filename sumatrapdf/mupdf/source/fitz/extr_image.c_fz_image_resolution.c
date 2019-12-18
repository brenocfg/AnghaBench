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
struct TYPE_3__ {int xres; int yres; } ;
typedef  TYPE_1__ fz_image ;

/* Variables and functions */
 int INSANE_DPI ; 
 int SANE_DPI ; 

void
fz_image_resolution(fz_image *image, int *xres, int *yres)
{
	*xres = image->xres;
	*yres = image->yres;
	if (*xres < 0 || *yres < 0 || (*xres == 0 && *yres == 0))
	{
		/* If neither xres or yres is sane, pick a sane value */
		*xres = SANE_DPI; *yres = SANE_DPI;
	}
	else if (*xres == 0)
	{
		*xres = *yres;
	}
	else if (*yres == 0)
	{
		*yres = *xres;
	}

	/* Scale xres and yres up until we get believable values */
	if (*xres < SANE_DPI || *yres < SANE_DPI || *xres > INSANE_DPI || *yres > INSANE_DPI)
	{
		if (*xres == *yres)
		{
			*xres = SANE_DPI;
			*yres = SANE_DPI;
		}
		else if (*xres < *yres)
		{
			*yres = *yres * SANE_DPI / *xres;
			*xres = SANE_DPI;
		}
		else
		{
			*xres = *xres * SANE_DPI / *yres;
			*yres = SANE_DPI;
		}
	}
}