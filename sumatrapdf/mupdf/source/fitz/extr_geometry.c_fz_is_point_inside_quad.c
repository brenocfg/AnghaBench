#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  fz_quad ;
typedef  int /*<<< orphan*/  fz_point ;

/* Variables and functions */
 int fz_is_point_inside_rect (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fz_rect_from_quad (int /*<<< orphan*/ ) ; 

int fz_is_point_inside_quad(fz_point p, fz_quad q)
{
	// TODO: non-rectilinear quads
	return fz_is_point_inside_rect(p, fz_rect_from_quad(q));
}