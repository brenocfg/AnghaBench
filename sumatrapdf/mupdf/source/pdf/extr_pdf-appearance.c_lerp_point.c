#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {float x; float y; } ;
typedef  TYPE_1__ fz_point ;

/* Variables and functions */
 TYPE_1__ fz_make_point (float,float) ; 

__attribute__((used)) static fz_point
lerp_point(fz_point a, fz_point b, float t)
{
	return fz_make_point(a.x + t * (b.x - a.x), a.y + t * (b.y - a.y));
}