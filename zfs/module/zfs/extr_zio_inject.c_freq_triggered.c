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
typedef  int uint32_t ;
typedef  int boolean_t ;

/* Variables and functions */
 int B_TRUE ; 
 int ZI_PERCENTAGE_MAX ; 
 int spa_get_random (int) ; 

__attribute__((used)) static boolean_t
freq_triggered(uint32_t frequency)
{
	/*
	 * zero implies always (100%)
	 */
	if (frequency == 0)
		return (B_TRUE);

	/*
	 * Note: we still handle legacy (unscaled) frequency values
	 */
	uint32_t maximum = (frequency <= 100) ? 100 : ZI_PERCENTAGE_MAX;

	return (spa_get_random(maximum) < frequency);
}