#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_8__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {unsigned char* samples; int n; int stride; int w; scalar_t__ h; } ;
typedef  TYPE_1__ fz_pixmap ;
struct TYPE_12__ {int x0; int y0; int x1; scalar_t__ y1; } ;
typedef  TYPE_2__ fz_irect ;
struct TYPE_13__ {int n; unsigned char* colorkey; TYPE_8__* mask; } ;
typedef  TYPE_3__ fz_image ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_14__ {scalar_t__ w; scalar_t__ h; } ;

/* Variables and functions */
 unsigned char fz_clampi (unsigned char,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_drop_pixmap (int /*<<< orphan*/ *,TYPE_1__*) ; 
 TYPE_1__* fz_get_pixmap_from_image (int /*<<< orphan*/ *,TYPE_8__*,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
fz_unblend_masked_tile(fz_context *ctx, fz_pixmap *tile, fz_image *image, const fz_irect *isa)
{
	fz_pixmap *mask;
	unsigned char *s, *d = tile->samples;
	int n = tile->n;
	int k;
	int sstride, dstride = tile->stride - tile->w * tile->n;
	int h;
	fz_irect subarea;

	/* We need at least as much of the mask as there was of the tile. */
	if (isa)
		subarea = *isa;
	else
	{
		subarea.x0 = 0;
		subarea.y0 = 0;
		subarea.x1 = tile->w;
		subarea.y1 = tile->h;
	}

	mask = fz_get_pixmap_from_image(ctx, image->mask, &subarea, NULL, NULL, NULL);
	s = mask->samples;
	/* RJW: Urgh, bit of nastiness here. fz_pixmap_from_image will either return
	 * an exact match for the subarea we asked for, or the full image, and the
	 * normal way to know is that the matrix will be updated. That doesn't help
	 * us here. */
	if (image->mask->w == mask->w && image->mask->h == mask->h) {
		subarea.x0 = 0;
		subarea.y0 = 0;
	}
	if (isa)
		s += (isa->x0 - subarea.x0) * mask->n + (isa->y0 - subarea.y0) * mask->stride;
	sstride = mask->stride - tile->w * mask->n;
	h = tile->h;

	if (tile->w != 0)
	{
		while (h--)
		{
			int w = tile->w;
			do
			{
				if (*s == 0)
					for (k = 0; k < image->n; k++)
						d[k] = image->colorkey[k];
				else
					for (k = 0; k < image->n; k++)
						d[k] = fz_clampi(image->colorkey[k] + (d[k] - image->colorkey[k]) * 255 / *s, 0, 255);
				s++;
				d += n;
			}
			while (--w);
			s += sstride;
			d += dstride;
		}
	}

	fz_drop_pixmap(ctx, mask);
}