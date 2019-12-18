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
 double equation_of_time (double) ; 
 double jcent_from_jd (double) ; 
 double jd_from_jcent (double) ; 

__attribute__((used)) static double
time_of_solar_noon(double t, double lon)
{
	/* First pass uses approximate solar noon to
	   calculate equation of time. */
	double t_noon = jcent_from_jd(jd_from_jcent(t) - lon/360.0);
	double eq_time = equation_of_time(t_noon);
	double sol_noon = 720 - 4*lon - eq_time;

	/* Recalculate using new solar noon. */
	t_noon = jcent_from_jd(jd_from_jcent(t) - 0.5 + sol_noon/1440.0);
	eq_time = equation_of_time(t_noon);
	sol_noon = 720 - 4*lon - eq_time;

	/* No need to do more iterations */
	return sol_noon;
}