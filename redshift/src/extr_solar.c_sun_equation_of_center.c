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
 double RAD (double) ; 
 double sin (int) ; 
 double sun_geom_mean_anomaly (double) ; 

__attribute__((used)) static double
sun_equation_of_center(double t)
{
	/* Use the first three terms of the equation. */
	double m = sun_geom_mean_anomaly(t);
	double c = sin(m)*(1.914602 - t*(0.004817 + 0.000014*t)) +
		sin(2*m)*(0.019993 - 0.000101*t) +
		sin(3*m)*0.000289;
	return RAD(c);
}