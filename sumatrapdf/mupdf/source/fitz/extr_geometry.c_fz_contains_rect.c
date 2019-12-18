#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; } ;
typedef  TYPE_1__ fz_rect ;

/* Variables and functions */
 scalar_t__ fz_is_empty_rect (TYPE_1__) ; 

int fz_contains_rect(fz_rect a, fz_rect b)
{
	if (fz_is_empty_rect(b))
		return 1;
	if (fz_is_empty_rect(a))
		return 0;
	return ((a.x0 <= b.x0) &&
		(a.y0 <= b.y0) &&
		(a.x1 >= b.x1) &&
		(a.y1 >= b.y1));
}