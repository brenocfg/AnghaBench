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
struct TYPE_5__ {int lo; int hi; } ;
typedef  TYPE_1__ pdf_hmtx ;
struct TYPE_6__ {int hmtx_len; TYPE_1__ dhmtx; TYPE_1__* hmtx; } ;
typedef  TYPE_2__ pdf_font_desc ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */

pdf_hmtx
pdf_lookup_hmtx(fz_context *ctx, pdf_font_desc *font, int cid)
{
	int l = 0;
	int r = font->hmtx_len - 1;
	int m;

	if (!font->hmtx)
		goto notfound;

	while (l <= r)
	{
		m = (l + r) >> 1;
		if (cid < font->hmtx[m].lo)
			r = m - 1;
		else if (cid > font->hmtx[m].hi)
			l = m + 1;
		else
			return font->hmtx[m];
	}

notfound:
	return font->dhmtx;
}