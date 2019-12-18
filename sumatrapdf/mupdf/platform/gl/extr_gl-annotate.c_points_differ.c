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
 float fz_abs (scalar_t__) ; 

__attribute__((used)) static int points_differ(fz_point a, fz_point b, float threshold)
{
	if (fz_abs(a.x - b.x) > threshold) return 1;
	if (fz_abs(a.y - b.y) > threshold) return 1;
	return 0;
}