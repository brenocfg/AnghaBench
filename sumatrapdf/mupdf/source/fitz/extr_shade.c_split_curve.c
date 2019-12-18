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
struct TYPE_5__ {float x; float y; } ;
typedef  TYPE_1__ fz_point ;

/* Variables and functions */

__attribute__((used)) static void
split_curve(fz_point *pole, fz_point *q0, fz_point *q1, int polestep)
{
	/*
	split bezier curve given by control points pole[0]..pole[3]
	using de casteljau algo at midpoint and build two new
	bezier curves q0[0]..q0[3] and q1[0]..q1[3]. all indices
	should be multiplies by polestep == 1 for vertical bezier
	curves in patch and == 4 for horizontal bezier curves due
	to C's multi-dimensional matrix memory layout.
	*/

	float x12 = (pole[1 * polestep].x + pole[2 * polestep].x) * 0.5f;
	float y12 = (pole[1 * polestep].y + pole[2 * polestep].y) * 0.5f;

	q0[1 * polestep].x = (pole[0 * polestep].x + pole[1 * polestep].x) * 0.5f;
	q0[1 * polestep].y = (pole[0 * polestep].y + pole[1 * polestep].y) * 0.5f;
	q1[2 * polestep].x = (pole[2 * polestep].x + pole[3 * polestep].x) * 0.5f;
	q1[2 * polestep].y = (pole[2 * polestep].y + pole[3 * polestep].y) * 0.5f;

	q0[2 * polestep].x = (q0[1 * polestep].x + x12) * 0.5f;
	q0[2 * polestep].y = (q0[1 * polestep].y + y12) * 0.5f;
	q1[1 * polestep].x = (x12 + q1[2 * polestep].x) * 0.5f;
	q1[1 * polestep].y = (y12 + q1[2 * polestep].y) * 0.5f;

	q0[3 * polestep].x = (q0[2 * polestep].x + q1[1 * polestep].x) * 0.5f;
	q0[3 * polestep].y = (q0[2 * polestep].y + q1[1 * polestep].y) * 0.5f;
	q1[0 * polestep].x = (q0[2 * polestep].x + q1[1 * polestep].x) * 0.5f;
	q1[0 * polestep].y = (q0[2 * polestep].y + q1[1 * polestep].y) * 0.5f;

	q0[0 * polestep].x = pole[0 * polestep].x;
	q0[0 * polestep].y = pole[0 * polestep].y;
	q1[3 * polestep].x = pole[3 * polestep].x;
	q1[3 * polestep].y = pole[3 * polestep].y;
}