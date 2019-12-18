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
 double acos (int) ; 
 double copysign (double,double) ; 
 int cos (double) ; 
 double fabs (double) ; 
 int sin (double) ; 

__attribute__((used)) static double
hour_angle_from_elevation(double lat, double decl, double elev)
{
	double omega = acos((cos(fabs(elev)) - sin(RAD(lat))*sin(decl))/
			    (cos(RAD(lat))*cos(decl)));
	return copysign(omega, -elev);
}