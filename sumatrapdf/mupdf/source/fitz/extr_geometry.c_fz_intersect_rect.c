#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {scalar_t__ x0; scalar_t__ y0; scalar_t__ x1; scalar_t__ y1; } ;
typedef  TYPE_1__ fz_rect ;

/* Variables and functions */
 TYPE_1__ fz_empty_rect ; 
 scalar_t__ fz_is_empty_rect (TYPE_1__) ; 
 scalar_t__ fz_is_infinite_rect (TYPE_1__) ; 

fz_rect
fz_intersect_rect(fz_rect a, fz_rect b)
{
	/* Check for empty box before infinite box */
	if (fz_is_empty_rect(a)) return fz_empty_rect;
	if (fz_is_empty_rect(b)) return fz_empty_rect;
	if (fz_is_infinite_rect(b)) return a;
	if (fz_is_infinite_rect(a)) return b;
	if (a.x0 < b.x0)
		a.x0 = b.x0;
	if (a.y0 < b.y0)
		a.y0 = b.y0;
	if (a.x1 > b.x1)
		a.x1 = b.x1;
	if (a.y1 > b.y1)
		a.y1 = b.y1;
	if (a.x1 < a.x0 || a.y1 < a.y0)
		return fz_empty_rect;
	return a;
}