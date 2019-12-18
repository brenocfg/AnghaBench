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
 int SOLAR_TIME_MAX ; 
 size_t SOLAR_TIME_MIDNIGHT ; 
 size_t SOLAR_TIME_NOON ; 
 double epoch_from_jd (double) ; 
 double jcent_from_jd (double) ; 
 double jd_from_epoch (double) ; 
 double round (double) ; 
 double* time_angle ; 
 double time_of_solar_elevation (double,double,double,double,double) ; 
 double time_of_solar_noon (double,double) ; 

void
solar_table_fill(double date, double lat, double lon, double *table)
{
	/* Calculate Julian day */
	double jd = jd_from_epoch(date);

	/* Calculate Julian day number */
	double jdn = round(jd);
	double t = jcent_from_jd(jdn);

	/* Calculate apparent solar noon */
	double sol_noon = time_of_solar_noon(t, lon);
	double j_noon = jdn - 0.5 + sol_noon/1440.0;
	double t_noon = jcent_from_jd(j_noon);
	table[SOLAR_TIME_NOON] = epoch_from_jd(j_noon);

	/* Calculate solar midnight */
	table[SOLAR_TIME_MIDNIGHT] = epoch_from_jd(j_noon + 0.5);

	/* Calulate absoute time of other phenomena */
	for (int i = 2; i < SOLAR_TIME_MAX; i++) {
		double angle = time_angle[i];
		double offset =
			time_of_solar_elevation(t, t_noon, lat, lon, angle);
		table[i] = epoch_from_jd(jdn - 0.5 + offset/1440.0);
	}
}