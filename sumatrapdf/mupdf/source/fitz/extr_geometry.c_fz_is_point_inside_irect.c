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
struct TYPE_3__ {int x0; int x1; int y0; int y1; } ;
typedef  TYPE_1__ fz_irect ;

/* Variables and functions */

int fz_is_point_inside_irect(int x, int y, fz_irect r)
{
	return (x >= r.x0 && x < r.x1 && y >= r.y0 && y < r.y1);
}