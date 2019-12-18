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
struct TYPE_4__ {float x; float y; } ;
typedef  TYPE_1__ fz_point ;

/* Variables and functions */

__attribute__((used)) static float
vec_dot(const fz_point *a, const fz_point *b)
{
	return a->x * b->x + a->y * b->y;
}