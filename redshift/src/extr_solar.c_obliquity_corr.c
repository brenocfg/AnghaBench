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
 double cos (double) ; 
 double mean_ecliptic_obliquity (double) ; 

__attribute__((used)) static double
obliquity_corr(double t)
{
	double e_0 = mean_ecliptic_obliquity(t);
	double omega = 125.04 - t*1934.136;
	return RAD(DEG(e_0) + 0.00256*cos(RAD(omega)));
}