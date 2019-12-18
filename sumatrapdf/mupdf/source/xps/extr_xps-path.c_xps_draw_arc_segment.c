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
typedef  int /*<<< orphan*/  xps_document ;
struct TYPE_3__ {int /*<<< orphan*/  y; int /*<<< orphan*/  x; } ;
typedef  TYPE_1__ fz_point ;
typedef  int /*<<< orphan*/  fz_path ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 int FZ_PI ; 
 int /*<<< orphan*/  cosf (float) ; 
 int /*<<< orphan*/  fz_lineto (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__ fz_transform_point_xy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sinf (float) ; 

__attribute__((used)) static void
xps_draw_arc_segment(fz_context *ctx, xps_document *doc, fz_path *path, fz_matrix mtx, float th0, float th1, int iscw)
{
	float t, d;
	fz_point p;

	while (th1 < th0)
		th1 += FZ_PI * 2;

	d = FZ_PI / 180; /* 1-degree precision */

	if (iscw)
	{
		for (t = th0 + d; t < th1 - d/2; t += d)
		{
			p = fz_transform_point_xy(cosf(t), sinf(t), mtx);
			fz_lineto(ctx, path, p.x, p.y);
		}
	}
	else
	{
		th0 += FZ_PI * 2;
		for (t = th0 - d; t > th1 + d/2; t -= d)
		{
			p = fz_transform_point_xy(cosf(t), sinf(t), mtx);
			fz_lineto(ctx, path, p.x, p.y);
		}
	}
}