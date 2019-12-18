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
typedef  int /*<<< orphan*/  (* fz_solid_color_painter_t ) (unsigned char*,int,int,unsigned char*,int,int /*<<< orphan*/ *) ;
struct TYPE_3__ {int alpha; int x; unsigned char* samples; int y; int stride; int n; scalar_t__ w; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;
typedef  int /*<<< orphan*/  fz_irect ;

/* Variables and functions */
 int fz_clampi (int,int,scalar_t__) ; 
 int /*<<< orphan*/  memset (unsigned char*,int,int) ; 
 int /*<<< orphan*/  stub1 (unsigned char*,int,int,unsigned char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
blit_sharp(int x0, int x1, int y, const fz_irect *clip, fz_pixmap *dst, unsigned char *color, fz_solid_color_painter_t *fn, fz_overprint *eop)
{
	unsigned char *dp;
	int da = dst->alpha;
	x0 = fz_clampi(x0, dst->x, dst->x + dst->w);
	x1 = fz_clampi(x1, dst->x, dst->x + dst->w);
	if (x0 < x1)
	{
		dp = dst->samples + (unsigned int)((y - dst->y) * dst->stride + (x0 - dst->x) * dst->n);
		if (color)
			(*fn)(dp, dst->n, x1 - x0, color, da, eop);
		else
			memset(dp, 255, x1-x0);
	}
}