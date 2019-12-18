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
 double asin (int) ; 
 double obliquity_corr (double) ; 
 int sin (double) ; 
 double sun_apparent_lon (double) ; 

__attribute__((used)) static double
solar_declination(double t)
{
	double e = obliquity_corr(t);
	double lambda = sun_apparent_lon(t);
	return asin(sin(e)*sin(lambda));
}