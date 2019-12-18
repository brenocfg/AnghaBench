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

/* Variables and functions */
 double sun_equation_of_center (double) ; 
 double sun_geom_mean_lon (double) ; 

__attribute__((used)) static double
sun_true_lon(double t)
{
	double l_0 = sun_geom_mean_lon(t);
	double c = sun_equation_of_center(t);
	return l_0 + c;
}