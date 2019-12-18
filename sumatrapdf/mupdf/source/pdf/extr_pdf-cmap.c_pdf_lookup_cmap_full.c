#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int low; unsigned int high; unsigned int out; } ;
typedef  TYPE_1__ pdf_xrange ;
struct TYPE_7__ {unsigned int low; unsigned int high; unsigned int out; } ;
typedef  TYPE_2__ pdf_range ;
struct TYPE_8__ {unsigned int low; size_t out; } ;
typedef  TYPE_3__ pdf_mrange ;
struct TYPE_9__ {int rlen; int xlen; int mlen; int* dict; struct TYPE_9__* usecmap; TYPE_3__* mranges; TYPE_1__* xranges; TYPE_2__* ranges; } ;
typedef  TYPE_4__ pdf_cmap ;

/* Variables and functions */

int
pdf_lookup_cmap_full(pdf_cmap *cmap, unsigned int cpt, int *out)
{
	pdf_range *ranges = cmap->ranges;
	pdf_xrange *xranges = cmap->xranges;
	pdf_mrange *mranges = cmap->mranges;
	unsigned int i;
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
		{
			out[0] = cpt - ranges[m].low + ranges[m].out;
			return 1;
		}
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
		{
			out[0] = cpt - xranges[m].low + xranges[m].out;
			return 1;
		}
	}

	l = 0;
	r = cmap->mlen - 1;
	while (l <= r)
	{
		m = (l + r) >> 1;
		if (cpt < mranges[m].low)
			r = m - 1;
		else if (cpt > mranges[m].low)
			l = m + 1;
		else
		{
			int *ptr = &cmap->dict[cmap->mranges[m].out];
			unsigned int len = (unsigned int)*ptr++;
			for (i = 0; i < len; ++i)
				out[i] = *ptr++;
			return len;
		}
	}

	if (cmap->usecmap)
		return pdf_lookup_cmap_full(cmap->usecmap, cpt, out);

	return 0;
}