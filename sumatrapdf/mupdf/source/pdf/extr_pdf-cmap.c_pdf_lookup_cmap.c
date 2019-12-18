#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {unsigned int low; unsigned int high; unsigned int out; } ;
typedef  TYPE_1__ pdf_xrange ;
struct TYPE_6__ {unsigned int low; unsigned int high; unsigned int out; } ;
typedef  TYPE_2__ pdf_range ;
struct TYPE_7__ {int rlen; int xlen; struct TYPE_7__* usecmap; TYPE_1__* xranges; TYPE_2__* ranges; } ;
typedef  TYPE_3__ pdf_cmap ;

/* Variables and functions */

int
pdf_lookup_cmap(pdf_cmap *cmap, unsigned int cpt)
{
	pdf_range *ranges = cmap->ranges;
	pdf_xrange *xranges = cmap->xranges;
	int l, r, m;

	l = 0;
	r = cmap->rlen - 1;
	while (l <= r)
	{
		m = (l + r) >> 1;
		if (cpt < ranges[m].low)
			r = m - 1;
		else if (cpt > ranges[m].high)
			l = m + 1;
		else
			return cpt - ranges[m].low + ranges[m].out;
	}

	l = 0;
	r = cmap->xlen - 1;
	while (l <= r)
	{
		m = (l + r) >> 1;
		if (cpt < xranges[m].low)
			r = m - 1;
		else if (cpt > xranges[m].high)
			l = m + 1;
		else
			return cpt - xranges[m].low + xranges[m].out;
	}

	if (cmap->usecmap)
		return pdf_lookup_cmap(cmap->usecmap, cpt);

	return -1;
}