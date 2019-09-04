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
 int /*<<< orphan*/  WARN (char*) ; 
 scalar_t__ _isnan (double) ; 

double _nextafter( double x, double y )
{
    WARN("This function is not implemented correctly\n");
	if ( x == y)
		return x;

	if ( _isnan(x) || _isnan(y) )
		return x;

	return x;
}