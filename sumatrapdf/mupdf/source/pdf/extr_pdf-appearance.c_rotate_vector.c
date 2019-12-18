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
typedef  int /*<<< orphan*/  fz_point ;

/* Variables and functions */
 float cosf (float) ; 
 int /*<<< orphan*/  fz_make_point (float,float) ; 
 float sinf (float) ; 

__attribute__((used)) static fz_point rotate_vector(float angle, float x, float y)
{
	float ca = cosf(angle);
	float sa = sinf(angle);
	return fz_make_point(x*ca - y*sa, x*sa + y*ca);
}