#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int codespace_len; TYPE_1__* codespace; } ;
typedef  TYPE_2__ pdf_cmap ;
struct TYPE_4__ {int n; unsigned int low; unsigned int high; } ;

/* Variables and functions */

int
pdf_decode_cmap(pdf_cmap *cmap, unsigned char *buf, unsigned char *end, unsigned int *cpt)
{
	unsigned int c;
	int k, n;
	int len = end - buf;

	if (len > 4)
		len = 4;

	c = 0;
	for (n = 0; n < len; n++)
	{
		c = (c << 8) | buf[n];
		for (k = 0; k < cmap->codespace_len; k++)
		{
			if (cmap->codespace[k].n == n + 1)
			{
				if (c >= cmap->codespace[k].low && c <= cmap->codespace[k].high)
				{
					*cpt = c;
					return n + 1;
				}
			}
		}
	}

	*cpt = 0;
	return 1;
}