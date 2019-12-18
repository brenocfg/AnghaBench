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
typedef  int /*<<< orphan*/  (* fz_span_painter_t ) (unsigned char*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ;
typedef  int /*<<< orphan*/  (* fz_span_color_painter_t ) (unsigned char*,unsigned char*,int,int,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ;
struct TYPE_3__ {unsigned char* samples; int y; int stride; int x; int n; int /*<<< orphan*/  alpha; } ;
typedef  TYPE_1__ fz_pixmap ;
typedef  int /*<<< orphan*/  fz_overprint ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (unsigned char*,unsigned char*,int,int,unsigned char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub2 (unsigned char*,int /*<<< orphan*/ ,unsigned char*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline void
blit_aa(fz_pixmap *dst, int x, int y, unsigned char *mp, int w, unsigned char *color, void *fn, fz_overprint *eop)
{
	unsigned char *dp;
	dp = dst->samples + (unsigned int)((y - dst->y) * dst->stride + (x - dst->x) * dst->n);
	if (color)
		(*(fz_span_color_painter_t *)fn)(dp, mp, dst->n, w, color, dst->alpha, eop);
	else
		(*(fz_span_painter_t *)fn)(dp, dst->alpha, mp, 1, 0, w, 255, eop);
}