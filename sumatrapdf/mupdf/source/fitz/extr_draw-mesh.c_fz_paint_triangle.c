#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {scalar_t__ w; scalar_t__ x; } ;
typedef  TYPE_1__ fz_pixmap ;
struct TYPE_10__ {float y0; float y1; int /*<<< orphan*/  x1; int /*<<< orphan*/  x0; } ;
typedef  TYPE_2__ fz_irect ;
struct TYPE_11__ {int /*<<< orphan*/ * v; scalar_t__ x; } ;
typedef  TYPE_3__ edge_data ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 float ceilf (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_max (float,float) ; 
 int fz_maxi (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  fz_min (float,float) ; 
 int fz_mini (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  paint_scan (TYPE_1__*,float,int,int,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  prepare_edge (float*,float*,TYPE_3__*,float,int) ; 
 int /*<<< orphan*/  step_edge (TYPE_3__*,int) ; 

__attribute__((used)) static void
fz_paint_triangle(fz_pixmap *pix, float *v[3], int n, fz_irect bbox)
{
	edge_data e0, e1;
	int top, mid, bot;
	float y, y1;
	int minx, maxx;

	top = bot = 0;
	if (v[1][1] < v[0][1]) top = 1; else bot = 1;
	if (v[2][1] < v[top][1]) top = 2;
	else if (v[2][1] > v[bot][1]) bot = 2;
	if (v[top][1] == v[bot][1]) return;

	/* Test if the triangle is completely outside the scissor rect */
	if (v[bot][1] < bbox.y0) return;
	if (v[top][1] > bbox.y1) return;

	/* Magic! Ensure that mid/top/bot are all different */
	mid = 3^top^bot;

	assert(top != bot && top != mid && mid != bot);

	minx = fz_maxi(bbox.x0, pix->x);
	maxx = fz_mini(bbox.x1, pix->x + pix->w);

	y = ceilf(fz_max(bbox.y0, v[top][1]));
	y1 = ceilf(fz_min(bbox.y1, v[mid][1]));

	n -= 2;
	prepare_edge(v[top], v[bot], &e0, y, n);
	if (y < y1)
	{
		prepare_edge(v[top], v[mid], &e1, y, n);

		do
		{
			paint_scan(pix, y, (int)e0.x, (int)e1.x, minx, maxx, &e0.v[0], &e1.v[0], n);
			step_edge(&e0, n);
			step_edge(&e1, n);
			y ++;
		}
		while (y < y1);
	}

	y1 = ceilf(fz_min(bbox.y1, v[bot][1]));
	if (y < y1)
	{
		prepare_edge(v[mid], v[bot], &e1, y, n);

		do
		{
			paint_scan(pix, y, (int)e0.x, (int)e1.x, minx, maxx, &e0.v[0], &e1.v[0], n);
			y ++;
			if (y >= y1)
				break;
			step_edge(&e0, n);
			step_edge(&e1, n);
		}
		while (1);
	}
}