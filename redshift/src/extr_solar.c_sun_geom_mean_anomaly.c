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

__attribute__((used)) static double
sun_geom_mean_anomaly(double t)
{
	return RAD(357.52911 + t*(35999.05029 - t*0.0001537));
}