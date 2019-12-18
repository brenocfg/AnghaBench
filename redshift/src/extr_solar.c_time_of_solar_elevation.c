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
 double equation_of_time (double) ; 
 double hour_angle_from_elevation (double,double,double) ; 
 double jcent_from_jd (scalar_t__) ; 
 scalar_t__ jd_from_jcent (double) ; 
 double solar_declination (double) ; 

__attribute__((used)) static double
time_of_solar_elevation(double t, double t_noon,
			double lat, double lon, double elev)
{
	/* First pass uses approximate sunrise to
	   calculate equation of time. */
	double eq_time = equation_of_time(t_noon);
	double sol_decl = solar_declination(t_noon);
	double ha = hour_angle_from_elevation(lat, sol_decl, elev);
	double sol_offset = 720 - 4*(lon + DEG(ha)) - eq_time;

	/* Recalculate using new sunrise. */
	double t_rise = jcent_from_jd(jd_from_jcent(t) + sol_offset/1440.0);
	eq_time = equation_of_time(t_rise);
	sol_decl = solar_declination(t_rise);
	ha = hour_angle_from_elevation(lat, sol_decl, elev);
	sol_offset = 720 - 4*(lon + DEG(ha)) - eq_time;

	/* No need to do more iterations */
	return sol_offset;
}