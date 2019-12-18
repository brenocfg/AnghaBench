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
 double floor (double) ; 
 scalar_t__ isinf (double) ; 
 scalar_t__ isnan (double) ; 

__attribute__((used)) static double jsM_round(double x)
{
	if (isnan(x)) return x;
	if (isinf(x)) return x;
	if (x == 0) return x;
	if (x > 0 && x < 0.5) return 0;
	if (x < 0 && x >= -0.5) return -0;
	return floor(x + 0.5);
}