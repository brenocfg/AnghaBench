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
struct TYPE_6__ {void* y1; void* x1; void* y0; void* x0; } ;
typedef  TYPE_1__ fz_irect ;

/* Variables and functions */
 void* ADD_WITH_SAT (int,void*,int) ; 
 scalar_t__ fz_is_empty_irect (TYPE_1__) ; 
 scalar_t__ fz_is_infinite_irect (TYPE_1__) ; 

fz_irect
fz_translate_irect(fz_irect a, int xoff, int yoff)
{
	int t;

	if (fz_is_empty_irect(a)) return a;
	if (fz_is_infinite_irect(a)) return a;
	a.x0 = ADD_WITH_SAT(t, a.x0, xoff);
	a.y0 = ADD_WITH_SAT(t, a.y0, yoff);
	a.x1 = ADD_WITH_SAT(t, a.x1, xoff);
	a.y1 = ADD_WITH_SAT(t, a.y1, yoff);
	return a;
}