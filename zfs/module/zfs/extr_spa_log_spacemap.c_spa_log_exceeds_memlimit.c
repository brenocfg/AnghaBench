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
typedef  scalar_t__ uint64_t ;
typedef  int /*<<< orphan*/  spa_t ;
typedef  int /*<<< orphan*/  boolean_t ;

/* Variables and functions */
 int /*<<< orphan*/  B_FALSE ; 
 int /*<<< orphan*/  B_TRUE ; 
 int PAGESIZE ; 
 int physmem ; 
 scalar_t__ spa_log_sm_memused (int /*<<< orphan*/ *) ; 
 scalar_t__ zfs_unflushed_max_mem_amt ; 
 int zfs_unflushed_max_mem_ppm ; 

__attribute__((used)) static boolean_t
spa_log_exceeds_memlimit(spa_t *spa)
{
	if (spa_log_sm_memused(spa) > zfs_unflushed_max_mem_amt)
		return (B_TRUE);

	uint64_t system_mem_allowed = ((physmem * PAGESIZE) *
	    zfs_unflushed_max_mem_ppm) / 1000000;
	if (spa_log_sm_memused(spa) > system_mem_allowed)
		return (B_TRUE);

	return (B_FALSE);
}