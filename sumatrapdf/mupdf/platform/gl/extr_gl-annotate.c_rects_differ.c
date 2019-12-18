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
struct TYPE_4__ {scalar_t__ y1; scalar_t__ x1; scalar_t__ y0; scalar_t__ x0; } ;
typedef  TYPE_1__ fz_rect ;

/* Variables and functions */
 float fz_abs (scalar_t__) ; 

__attribute__((used)) static int rects_differ(fz_rect a, fz_rect b, float threshold)
{
	if (fz_abs(a.x0 - b.x0) > threshold) return 1;
	if (fz_abs(a.y0 - b.y0) > threshold) return 1;
	if (fz_abs(a.x1 - b.x1) > threshold) return 1;
	if (fz_abs(a.y1 - b.y1) > threshold) return 1;
	return 0;
}