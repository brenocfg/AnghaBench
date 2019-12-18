#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; } ;
typedef  TYPE_1__ fz_point ;
struct TYPE_7__ {float a; float c; float e; float b; float d; float f; } ;
typedef  TYPE_2__ fz_matrix ;

/* Variables and functions */

fz_point
fz_transform_point(fz_point p, fz_matrix m)
{
	float x = p.x;
	p.x = x * m.a + p.y * m.c + m.e;
	p.y = x * m.b + p.y * m.d + m.f;
	return p;
}