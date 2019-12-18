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
 double DEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  jcent_from_jd (double) ; 
 double jd_from_epoch (double) ; 
 int /*<<< orphan*/  solar_elevation_from_time (int /*<<< orphan*/ ,double,double) ; 

double
solar_elevation(double date, double lat, double lon)
{
	double jd = jd_from_epoch(date);
	return DEG(solar_elevation_from_time(jcent_from_jd(jd), lat, lon));
}