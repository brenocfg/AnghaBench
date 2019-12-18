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
struct TYPE_4__ {float x; float y; } ;
typedef  TYPE_1__ fz_point ;

/* Variables and functions */
 float acosf (float) ; 

__attribute__((used)) static float
angle_between(const fz_point u, const fz_point v)
{
	float det = u.x * v.y - u.y * v.x;
	float sign = (det < 0 ? -1 : 1);
	float magu = u.x * u.x + u.y * u.y;
	float magv = v.x * v.x + v.y * v.y;
	float udotv = u.x * v.x + u.y * v.y;
	float t = udotv / (magu * magv);
	/* guard against rounding errors when near |1| (where acos will return NaN) */
	if (t < -1) t = -1;
	if (t > 1) t = 1;
	return sign * acosf(t);
}