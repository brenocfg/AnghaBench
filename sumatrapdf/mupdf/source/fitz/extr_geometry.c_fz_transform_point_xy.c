#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ fz_point ;
struct TYPE_6__ {float a; float c; float b; float d; scalar_t__ f; scalar_t__ e; } ;
typedef  TYPE_2__ fz_matrix ;

/* Variables and functions */

fz_point
fz_transform_point_xy(float x, float y, fz_matrix m)
{
	fz_point p;
	p.x = x * m.a + y * m.c + m.e;
	p.y = x * m.b + y * m.d + m.f;
	return p;
}