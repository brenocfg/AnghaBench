#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {float** coords; scalar_t__* extend; } ;
struct TYPE_9__ {TYPE_1__ l_or_r; } ;
struct TYPE_10__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_shade ;
struct TYPE_11__ {float x; float y; } ;
typedef  TYPE_4__ fz_point ;
typedef  int /*<<< orphan*/  fz_mesh_processor ;
typedef  int /*<<< orphan*/  fz_matrix ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 float HUGENUM ; 
 int fz_matrix_expansion (int /*<<< orphan*/ ) ; 
 int fz_max (float,float) ; 
 int /*<<< orphan*/  fz_paint_annulus (int /*<<< orphan*/ *,int /*<<< orphan*/ ,TYPE_4__,float,int,TYPE_4__,float,int,int,int /*<<< orphan*/ *) ; 
 int sqrtf (int) ; 

__attribute__((used)) static void
fz_process_shade_type3(fz_context *ctx, fz_shade *shade, fz_matrix ctm, fz_mesh_processor *painter)
{
	fz_point p0, p1;
	float r0, r1;
	fz_point e;
	float er, rs;
	int count;

	p0.x = shade->u.l_or_r.coords[0][0];
	p0.y = shade->u.l_or_r.coords[0][1];
	r0 = shade->u.l_or_r.coords[0][2];

	p1.x = shade->u.l_or_r.coords[1][0];
	p1.y = shade->u.l_or_r.coords[1][1];
	r1 = shade->u.l_or_r.coords[1][2];

	/* number of segments for a half-circle */
	count = 4 * sqrtf(fz_matrix_expansion(ctm) * fz_max(r0, r1));
	if (count < 3)
		count = 3;
	if (count > 1024)
		count = 1024;

	if (shade->u.l_or_r.extend[0])
	{
		if (r0 < r1)
			rs = r0 / (r0 - r1);
		else
			rs = -HUGENUM;

		e.x = p0.x + (p1.x - p0.x) * rs;
		e.y = p0.y + (p1.y - p0.y) * rs;
		er = r0 + (r1 - r0) * rs;

		fz_paint_annulus(ctx, ctm, e, er, 0, p0, r0, 0, count, painter);
	}

	fz_paint_annulus(ctx, ctm, p0, r0, 0, p1, r1, 1, count, painter);

	if (shade->u.l_or_r.extend[1])
	{
		if (r0 > r1)
			rs = r1 / (r1 - r0);
		else
			rs = -HUGENUM;

		e.x = p1.x + (p0.x - p1.x) * rs;
		e.y = p1.y + (p0.y - p1.y) * rs;
		er = r1 + (r0 - r1) * rs;

		fz_paint_annulus(ctx, ctm, p1, r1, 1, e, er, 1, count, painter);
	}
}