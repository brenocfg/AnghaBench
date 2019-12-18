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
 float sqrtf (float) ; 

fz_point
fz_normalize_vector(fz_point p)
{
	float len = p.x * p.x + p.y * p.y;
	if (len != 0)
	{
		len = sqrtf(len);
		p.x /= len;
		p.y /= len;
	}
	return p;
}