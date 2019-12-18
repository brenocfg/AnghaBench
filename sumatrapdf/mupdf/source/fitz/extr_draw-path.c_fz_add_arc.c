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
struct TYPE_4__ {float flatness; int /*<<< orphan*/  linewidth; } ;
typedef  TYPE_1__ sctx ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_PI ; 
 int FZ_SQRT2 ; 
 float atan2f (float,float) ; 
 int ceilf (float) ; 
 float cosf (float) ; 
 float fabsf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_add_line (int /*<<< orphan*/ *,TYPE_1__*,float,float,float,float,int) ; 
 float sinf (float) ; 
 int sqrtf (float) ; 

__attribute__((used)) static void
fz_add_arc(fz_context *ctx, sctx *s,
	float xc, float yc,
	float x0, float y0,
	float x1, float y1,
	int rev)
{
	float th0, th1, r;
	float theta;
	float ox, oy, nx, ny;
	int n, i;

	r = fabsf(s->linewidth);
	theta = 2 * FZ_SQRT2 * sqrtf(s->flatness / r);
	th0 = atan2f(y0, x0);
	th1 = atan2f(y1, x1);

	if (r > 0)
	{
		if (th0 < th1)
			th0 += FZ_PI * 2;
		n = ceilf((th0 - th1) / theta);
	}
	else
	{
		if (th1 < th0)
			th1 += FZ_PI * 2;
		n = ceilf((th1 - th0) / theta);
	}

	if (rev)
	{
		ox = x1;
		oy = y1;
		for (i = n-1; i > 0; i--)
		{
			theta = th0 + (th1 - th0) * i / n;
			nx = cosf(theta) * r;
			ny = sinf(theta) * r;
			fz_add_line(ctx, s, xc + nx, yc + ny, xc + ox, yc + oy, rev);
			ox = nx;
			oy = ny;
		}

		fz_add_line(ctx, s, xc + x0, yc + y0, xc + ox, yc + oy, rev);
	}
	else
	{
		ox = x0;
		oy = y0;
		for (i = 1; i < n; i++)
		{
			theta = th0 + (th1 - th0) * i / n;
			nx = cosf(theta) * r;
			ny = sinf(theta) * r;
			fz_add_line(ctx, s, xc + ox, yc + oy, xc + nx, yc + ny, rev);
			ox = nx;
			oy = ny;
		}

		fz_add_line(ctx, s, xc + ox, yc + oy, xc + x1, yc + y1, rev);
	}
}