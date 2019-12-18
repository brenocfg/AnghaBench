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
typedef  int int64_t ;
typedef  int /*<<< orphan*/  free_memory_reason_t ;

/* Variables and functions */
 int /*<<< orphan*/  FMR_UNKNOWN ; 
 int INT64_MAX ; 
 int last_free_memory ; 
 int /*<<< orphan*/  last_free_reason ; 
 scalar_t__ spa_get_random (int) ; 

int64_t
arc_available_memory(void)
{
	int64_t lowest = INT64_MAX;
	free_memory_reason_t r = FMR_UNKNOWN;

	/* Every 100 calls, free a small amount */
	if (spa_get_random(100) == 0)
		lowest = -1024;

	last_free_memory = lowest;
	last_free_reason = r;

	return (lowest);
}