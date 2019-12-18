#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {int n; int alpha; unsigned char* samples; int stride; int w; int h; int flags; int /*<<< orphan*/  seps; TYPE_3__* colorspace; } ;
typedef  TYPE_4__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_context ;
struct TYPE_15__ {int n; } ;
typedef  TYPE_5__ fz_colorspace ;
struct TYPE_11__ {int high; unsigned char* lookup; TYPE_5__* base; } ;
struct TYPE_12__ {TYPE_1__ indexed; } ;
struct TYPE_13__ {scalar_t__ type; TYPE_2__ u; } ;

/* Variables and functions */
 scalar_t__ FZ_COLORSPACE_INDEXED ; 
 int /*<<< orphan*/  FZ_ERROR_GENERIC ; 
 int FZ_PIXMAP_FLAG_INTERPOLATE ; 
 int fz_mini (int,int) ; 
 TYPE_4__* fz_new_pixmap_with_bbox (int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  fz_pixmap_bbox (int /*<<< orphan*/ *,TYPE_4__ const*) ; 
 int /*<<< orphan*/  fz_throw (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

fz_pixmap *
fz_convert_indexed_pixmap_to_base(fz_context *ctx, const fz_pixmap *src)
{
	fz_pixmap *dst;
	fz_colorspace *base;
	const unsigned char *s;
	unsigned char *d;
	int y, x, k, n, high;
	unsigned char *lookup;
	int s_line_inc, d_line_inc;

	if (src->colorspace->type != FZ_COLORSPACE_INDEXED)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot convert non-indexed pixmap");
	if (src->n != 1 + src->alpha)
		fz_throw(ctx, FZ_ERROR_GENERIC, "cannot convert indexed pixmap mis-matching components");

	base = src->colorspace->u.indexed.base;
	high = src->colorspace->u.indexed.high;
	lookup = src->colorspace->u.indexed.lookup;
	n = base->n;

	dst = fz_new_pixmap_with_bbox(ctx, base, fz_pixmap_bbox(ctx, src), src->seps, src->alpha);
	s = src->samples;
	d = dst->samples;
	s_line_inc = src->stride - src->w * src->n;
	d_line_inc = dst->stride - dst->w * dst->n;

	if (src->alpha)
	{
		for (y = 0; y < src->h; y++)
		{
			for (x = 0; x < src->w; x++)
			{
				int v = *s++;
				int a = *s++;
				int aa = a + (a>>7);
				v = fz_mini(v, high);
				for (k = 0; k < n; k++)
					*d++ = (aa * lookup[v * n + k] + 128)>>8;
				*d++ = a;
			}
			s += s_line_inc;
			d += d_line_inc;
		}
	}
	else
	{
		for (y = 0; y < src->h; y++)
		{
			for (x = 0; x < src->w; x++)
			{
				int v = *s++;
				v = fz_mini(v, high);
				for (k = 0; k < n; k++)
					*d++ = lookup[v * n + k];
			}
			s += s_line_inc;
			d += d_line_inc;
		}
	}

	if (src->flags & FZ_PIXMAP_FLAG_INTERPOLATE)
		dst->flags |= FZ_PIXMAP_FLAG_INTERPOLATE;
	else
		dst->flags &= ~FZ_PIXMAP_FLAG_INTERPOLATE;

	return dst;
}