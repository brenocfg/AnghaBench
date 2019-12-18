#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ptrdiff_t ;
struct TYPE_4__ {unsigned char* samples; size_t w; int h; int n; int s; int alpha; size_t stride; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int fz_div255 (int,int) ; 
 int fz_mini (int,int) ; 
 void* fz_mul255 (int,int) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void fast_bgr_to_cmyk(fz_context *ctx, fz_pixmap *src, fz_pixmap *dst, int copy_spots)
{
	unsigned char *s = src->samples;
	unsigned char *d = dst->samples;
	size_t w = src->w;
	int h = src->h;
	int sn = src->n;
	int ss = src->s;
	int sa = src->alpha;
	int dn = dst->n;
	int ds = dst->s;
	int da = dst->alpha;
	ptrdiff_t d_line_inc = dst->stride - w * dn;
	ptrdiff_t s_line_inc = src->stride - w * sn;
	int c, m, y, k, r, g, b;
	int a = 255;
	int i;

	if (copy_spots && ss != ds)
		fz_throw(ctx, FZ_ERROR_GENERIC, "incompatible number of spots when converting pixmap");

	if ((int)w < 0 || h < 0)
		fz_throw(ctx, FZ_ERROR_GENERIC, "integer overflow");

	while (h--)
	{
		size_t ww = w;
		while (ww--)
		{
			b = s[0];
			g = s[1];
			r = s[2];

			if (sa)
			{
				a = s[3+ss];
				r = fz_div255(r, a);
				g = fz_div255(g, a);
				b = fz_div255(b, a);
			}

			c = 255 - r;
			m = 255 - g;
			y = 255 - b;
			k = fz_mini(c, fz_mini(m, y));
			c = c - k;
			m = m - k;
			y = y - k;

			if (da)
			{
				*d++ = fz_mul255(c, a);
				*d++ = fz_mul255(m, a);
				*d++ = fz_mul255(y, a);
				*d++ = fz_mul255(k, a);
			}
			else
			{
				*d++ = c;
				*d++ = m;
				*d++ = y;
				*d++ = k;
			}

			if (copy_spots)
			{
				s += 3;
				for (i=ss; i > 0; --i)
					*d++ = *s++;
				s += sa;
			}
			else
			{
				s += 3 + ss + sa;
				d += ds;
			}

			if (da)
			{
				*d++ = a;
			}
		}
		d += d_line_inc;
		s += s_line_inc;
	}
}