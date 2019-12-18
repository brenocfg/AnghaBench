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
struct TYPE_5__ {unsigned char* samples; int stride; int n; int /*<<< orphan*/  h; int /*<<< orphan*/  y; int /*<<< orphan*/  w; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_pixmap ;
struct TYPE_6__ {int /*<<< orphan*/  y1; int /*<<< orphan*/  y0; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; } ;
typedef  TYPE_2__ fz_irect ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int fz_clampi (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void fz_invert_pixmap_rect(fz_context *ctx, fz_pixmap *image, fz_irect rect)
{
	unsigned char *p;
	int x, y, n;

	int x0 = fz_clampi(rect.x0 - image->x, 0, image->w);
	int x1 = fz_clampi(rect.x1 - image->x, 0, image->w);
	int y0 = fz_clampi(rect.y0 - image->y, 0, image->h);
	int y1 = fz_clampi(rect.y1 - image->y, 0, image->h);

	for (y = y0; y < y1; y++)
	{
		p = image->samples + (unsigned int)((y * image->stride) + (x0 * image->n));
		for (x = x0; x < x1; x++)
		{
			for (n = image->n; n > 1; n--, p++)
				*p = 255 - *p;
			p++;
		}
	}
}