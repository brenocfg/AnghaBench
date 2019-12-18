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
 double RAD (int) ; 
 double elevation_from_hour_angle (double,double,double) ; 
 double equation_of_time (double) ; 
 double jd_from_jcent (double) ; 
 double round (double) ; 
 double solar_declination (double) ; 

__attribute__((used)) static double
solar_elevation_from_time(double t, double lat, double lon)
{
	/* Minutes from midnight */
	double jd = jd_from_jcent(t);
	double offset = (jd - round(jd) - 0.5)*1440.0;

	double eq_time = equation_of_time(t);
	double ha = RAD((720 - offset - eq_time)/4 - lon);
	double decl = solar_declination(t);
	return elevation_from_hour_angle(lat, decl, ha);
}