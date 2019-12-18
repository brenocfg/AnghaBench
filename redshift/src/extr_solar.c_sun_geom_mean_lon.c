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
 double RAD (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fmod (double,int) ; 

__attribute__((used)) static double
sun_geom_mean_lon(double t)
{
	/* FIXME returned value should always be positive */
	return RAD(fmod(280.46646 + t*(36000.76983 + t*0.0003032), 360));
}