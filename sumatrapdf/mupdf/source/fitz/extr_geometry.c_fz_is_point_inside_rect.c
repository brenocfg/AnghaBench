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
struct TYPE_5__ {scalar_t__ x0; scalar_t__ x1; scalar_t__ y0; scalar_t__ y1; } ;
typedef  TYPE_1__ fz_rect ;
struct TYPE_6__ {scalar_t__ x; scalar_t__ y; } ;
typedef  TYPE_2__ fz_point ;

/* Variables and functions */

int fz_is_point_inside_rect(fz_point p, fz_rect r)
{
	return (p.x >= r.x0 && p.x < r.x1 && p.y >= r.y0 && p.y < r.y1);
}