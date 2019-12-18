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
mean_ecliptic_obliquity(double t)
{
	double sec = 21.448 - t*(46.815 + t*(0.00059 - t*0.001813));
	return RAD(23.0 + (26.0 + (sec/60.0))/60.0);
}