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
struct TYPE_3__ {float x; float y; float z; scalar_t__ w; } ;
typedef  TYPE_1__ plane ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 

__attribute__((used)) static int test_plane(plane *p, float x0, float y0, float z0, float x1, float y1, float z1)
{
   // return false if the box is entirely behind the plane
   float d=0;
   assert(x0 <= x1 && y0 <= y1 && z0 <= z1);
   if (p->x > 0) d += x1*p->x; else d += x0*p->x;
   if (p->y > 0) d += y1*p->y; else d += y0*p->y;
   if (p->z > 0) d += z1*p->z; else d += z0*p->z;
   return d + p->w >= 0;
}