#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int w; int n; int h; unsigned char* samples; int stride; int s; int /*<<< orphan*/  colorspace; scalar_t__ alpha; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 scalar_t__ fz_colorspace_is_subtractive (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,unsigned int) ; 

void
fz_clear_pixmap(fz_context *ctx, fz_pixmap *pix)
{
	int stride = pix->w * pix->n;
	int h = pix->h;
	unsigned char *s = pix->samples;
	if (stride == pix->stride)
	{
		stride *= h;
		h = 1;
	}
	if (pix->alpha || fz_colorspace_is_subtractive(ctx, pix->colorspace))
	{
		while (h--)
		{
			memset(s, 0, (unsigned int)stride);
			s += pix->stride;
		}
	}
	else if (pix->s == 0)
	{
		while (h--)
		{
			memset(s, 0xff, (unsigned int)stride);
			s += pix->stride;
		}
	}
	else
	{
		/* Horrible, slow case: additive with spots */
		int w = stride/pix->n;
		int spots = pix->s;
		int colorants = pix->n - spots; /* We know there is no alpha */
		while (h--)
		{
			int w2 = w;
			while (w2--)
			{
				int i = colorants;
				do
				{
					*s++ = 0xff;
					i--;
				}
				while (i != 0);

				i = spots;
				do
				{
					*s++ = 0;
					i--;
				}
				while (i != 0);
			}
		}
	}
}