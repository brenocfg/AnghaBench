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
struct TYPE_5__ {int x0; int x1; int y0; int y1; } ;
typedef  TYPE_1__ fz_irect ;
struct TYPE_6__ {int bpc; int n; int w; int h; } ;
typedef  TYPE_2__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

__attribute__((used)) static void fz_adjust_image_subarea(fz_context *ctx, fz_image *image, fz_irect *subarea, int l2factor)
{
	int f = 1<<l2factor;
	int bpp = image->bpc * image->n;
	int mask;

	switch (bpp)
	{
	case 1: mask = 8*f; break;
	case 2: mask = 4*f; break;
	case 4: mask = 2*f; break;
	default: mask = (bpp & 7) == 0 ? f : 0; break;
	}

	if (mask != 0)
	{
		subarea->x0 &= ~(mask - 1);
		subarea->x1 = (subarea->x1 + mask - 1) & ~(mask - 1);
	}
	else
	{
		/* Awkward case - mask cannot be a power of 2. */
		mask = bpp*f;
		switch (bpp)
		{
		case 3:
		case 5:
		case 7:
		case 9:
		case 11:
		case 13:
		case 15:
		default:
			mask *= 8;
			break;
		case 6:
		case 10:
		case 14:
			mask *= 4;
			break;
		case 12:
			mask *= 2;
			break;
		}
		subarea->x0 = (subarea->x0 / mask) * mask;
		subarea->x1 = ((subarea->x1 + mask - 1) / mask) * mask;
	}

	subarea->y0 &= ~(f - 1);
	if (subarea->x1 > image->w)
		subarea->x1 = image->w;
	subarea->y1 = (subarea->y1 + f - 1) & ~(f - 1);
	if (subarea->y1 > image->h)
		subarea->y1 = image->h;
}