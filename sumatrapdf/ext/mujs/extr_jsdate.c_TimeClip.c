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
 double NAN ; 
 double fabs (double) ; 
 double floor (double) ; 
 int /*<<< orphan*/  isfinite (double) ; 

__attribute__((used)) static double TimeClip(double t)
{
	if (!isfinite(t))
		return NAN;
	if (fabs(t) > 8.64e15)
		return NAN;
	return t < 0 ? -floor(-t) : floor(t);
}