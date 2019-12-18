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
 double DEG (double) ; 
 double RAD (double) ; 
 double sin (double) ; 
 double sun_true_lon (double) ; 

__attribute__((used)) static double
sun_apparent_lon(double t)
{
	double o = sun_true_lon(t);
	return RAD(DEG(o) - 0.00569 - 0.00478*sin(RAD(125.04 - 1934.136*t)));
}