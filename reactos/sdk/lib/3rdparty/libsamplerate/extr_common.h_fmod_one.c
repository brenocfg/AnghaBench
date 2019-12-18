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
 double lrint (double) ; 

__attribute__((used)) static inline double
fmod_one (double x)
{	double res ;

	res = x - lrint (x) ;
	if (res < 0.0)
		return res + 1.0 ;

	return res ;
}