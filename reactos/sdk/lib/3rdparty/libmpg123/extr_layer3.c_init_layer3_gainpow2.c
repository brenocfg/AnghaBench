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
typedef  int /*<<< orphan*/  real ;
typedef  int /*<<< orphan*/  mpg123_handle ;

/* Variables and functions */
 int /*<<< orphan*/  DOUBLE_TO_REAL_SCALE_LAYER3 (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * gainpow2 ; 
 int /*<<< orphan*/  pow (double,double) ; 

real init_layer3_gainpow2(mpg123_handle *fr, int i)
{
#if defined(REAL_IS_FIXED) && defined(PRECALC_TABLES)
	return gainpow2[i+256];
#else
	return DOUBLE_TO_REAL_SCALE_LAYER3(pow((double)2.0,-0.25 * (double) (i+210)),i+256);
#endif
}