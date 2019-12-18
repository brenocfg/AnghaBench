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
struct TYPE_4__ {scalar_t__ y; scalar_t__ x; } ;
typedef  TYPE_1__ fz_point ;

/* Variables and functions */
 float cosf (float) ; 
 float sinf (float) ; 

__attribute__((used)) static fz_point
fz_point_on_circle(fz_point p, float r, float theta)
{
	p.x = p.x + cosf(theta) * r;
	p.y = p.y + sinf(theta) * r;
	return p;
}