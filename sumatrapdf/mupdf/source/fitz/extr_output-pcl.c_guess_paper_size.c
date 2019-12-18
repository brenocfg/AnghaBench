#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ paper_size; int features; int orientation; } ;
typedef  TYPE_1__ fz_pcl_options ;
struct TYPE_6__ {void* code; int width; int height; } ;

/* Variables and functions */
 int INT_MAX ; 
 int PCL_CAN_SET_CUSTOM_PAPER_SIZE ; 
 int PCL_HAS_ORIENTATION ; 
 int PCL_HAS_RICOH_PAPER_SIZES ; 
 void* eCustomPaperSize ; 
 int num_elems (TYPE_2__*) ; 
 TYPE_2__* papersizes ; 

__attribute__((used)) static void guess_paper_size(fz_pcl_options *pcl, int w, int h, int xres, int yres)
{
	int size;
	int rotated = 0;

	/* If we've been given a paper size, live with it */
	if (pcl->paper_size != 0)
		return;

	w = w * 300 / xres;
	h = h * 300 / xres;

	/* Look for an exact match */
	for (size = 0; size < (int)num_elems(papersizes); size++)
	{
		if (papersizes[size].code > eCustomPaperSize && (pcl->features & PCL_HAS_RICOH_PAPER_SIZES) == 0)
			continue;
		if (w == papersizes[size].width && h == papersizes[size].height)
			break;
		if ((pcl->features & PCL_HAS_ORIENTATION) && w == papersizes[size].height && h == papersizes[size].width)
		{
			rotated = 1;
			break;
		}
	}

	/* If we didn't find an exact match, find the smallest one that's
	 * larger. Consider orientation if our printer supports it. */
	if (size == num_elems(papersizes))
	{
		if ((pcl->features & PCL_CAN_SET_CUSTOM_PAPER_SIZE) != 0)
		{
			/* Send it as a custom size */
			size = eCustomPaperSize;
		}
		else
		{
			/* Send the next larger one (minimise waste) */
			int i;
			int best_waste = INT_MAX;
			for (i = 0; i < (int)num_elems(papersizes); i++)
			{
				int waste;
				if (papersizes[i].code > eCustomPaperSize && (pcl->features & PCL_HAS_RICOH_PAPER_SIZES) == 0)
					continue;
				waste = papersizes[i].width * papersizes[i].height - w * h;
				if (waste > best_waste)
					continue;
				if (w <= papersizes[i].width && h <= papersizes[i].height)
				{
					best_waste = waste;
					rotated = 0;
					size = i;
				}
				if ((pcl->features & PCL_HAS_ORIENTATION) && w <= papersizes[i].height && h <= papersizes[i].width)
				{
					best_waste = waste;
					rotated = 1;
					size = i;
				}
			}
		}
	}

	/* Now, size = The best size we have (or num_elems(papersizes)) if it's too big */

	if (size < (int)num_elems(papersizes))
		pcl->paper_size = papersizes[size].code;
	else
		pcl->paper_size = eCustomPaperSize; /* Custom */

	pcl->orientation = rotated;
}