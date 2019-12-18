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

__attribute__((used)) static int
fade(fz_pixmap *tpix, const fz_pixmap *opix, const fz_pixmap *npix, int time)
{
	unsigned char *t, *o, *n;
	int size;
	int h;
	int tstride, ostride, nstride;

	if (!tpix || !opix || !npix || tpix->w != opix->w || opix->w != npix->w || tpix->h != opix->h || opix->h != npix->h || tpix->n != opix->n || opix->n != npix->n)
		return 0;
	h = tpix->h;
	size = tpix->w * tpix->n;
	ostride = opix->stride - size;
	nstride = npix->stride - size;
	tstride = tpix->stride - size;
	t = tpix->samples;
	o = opix->samples;
	n = npix->samples;
	while (h--)
	{
		int ww = size;
		while (ww-- > 0)
		{
			int op = *o++;
			int np = *n++;
			*t++ = ((op<<8) + ((np-op) * time) + 0x80)>>8;
		}
		o += ostride;
		n += nstride;
		t += tstride;
	}
	return 1;
}