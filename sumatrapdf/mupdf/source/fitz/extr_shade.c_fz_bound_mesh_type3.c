#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {float** coords; scalar_t__* extend; } ;
struct TYPE_10__ {TYPE_1__ l_or_r; } ;
struct TYPE_11__ {TYPE_2__ u; } ;
typedef  TYPE_3__ fz_shade ;
struct TYPE_12__ {float x0; float y0; float x1; float y1; } ;
typedef  TYPE_4__ fz_rect ;
struct TYPE_13__ {float x; float y; } ;
typedef  TYPE_5__ fz_point ;
typedef  int /*<<< orphan*/  fz_context ;

/* Variables and functions */
 TYPE_4__ fz_infinite_rect ; 

__attribute__((used)) static fz_rect
fz_bound_mesh_type3(fz_context *ctx, fz_shade *shade)
{
	fz_rect bbox;
	fz_point p0, p1;
	float r0, r1;

	r0 = shade->u.l_or_r.coords[0][2];
	r1 = shade->u.l_or_r.coords[1][2];

	if (shade->u.l_or_r.extend[0])
	{
		if (r0 >= r1)
			return fz_infinite_rect;
	}

	if (shade->u.l_or_r.extend[1])
	{
		if (r0 <= r1)
			return fz_infinite_rect;
	}

	p0.x = shade->u.l_or_r.coords[0][0];
	p0.y = shade->u.l_or_r.coords[0][1];
	p1.x = shade->u.l_or_r.coords[1][0];
	p1.y = shade->u.l_or_r.coords[1][1];

	bbox.x0 = p0.x - r0; bbox.y0 = p0.y - r0;
	bbox.x1 = p0.x + r0; bbox.y1 = p0.x + r0;
	if (bbox.x0 > p1.x - r1)
		bbox.x0 = p1.x - r1;
	if (bbox.x1 < p1.x + r1)
		bbox.x1 = p1.x + r1;
	if (bbox.y0 > p1.y - r1)
		bbox.y0 = p1.y - r1;
	if (bbox.y1 < p1.y + r1)
		bbox.y1 = p1.y + r1;
	return bbox;
}