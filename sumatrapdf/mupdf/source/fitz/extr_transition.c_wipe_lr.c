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
struct TYPE_5__ {scalar_t__ w; scalar_t__ h; scalar_t__ n; int stride; unsigned char* samples; } ;
typedef  TYPE_1__ fz_pixmap ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (unsigned char*,unsigned char*,int) ; 

__attribute__((used)) static int
wipe_lr(fz_pixmap *tpix, fz_pixmap *opix, fz_pixmap *npix, int time)
{
	unsigned char *t, *o, *n;
	int size, position, y;
	int tstride, ostride, nstride;

	if (!tpix || !opix || !npix || tpix->w != opix->w || opix->w != npix->w || tpix->h != opix->h || opix->h != npix->h || tpix->n != opix->n || opix->n != npix->n)
		return 0;
	size = tpix->w * tpix->n;
	position = tpix->w * time / 256;
	position *= tpix->n;
	ostride = opix->stride;
	nstride = npix->stride;
	tstride = tpix->stride;
	t = tpix->samples;
	o = opix->samples + position;
	n = npix->samples;
	for (y = 0; y < tpix->h; y++)
	{
		memcpy(t, n, position);
		memcpy(t+position, o, size-position);
		t += tstride;
		o += ostride;
		n += nstride;
	}
	return 1;
}