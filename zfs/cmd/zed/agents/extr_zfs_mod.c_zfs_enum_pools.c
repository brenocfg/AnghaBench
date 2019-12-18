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
 int /*<<< orphan*/  B_TRUE ; 
 int /*<<< orphan*/  g_enumeration_done ; 
 int /*<<< orphan*/  g_pool_list ; 
 int /*<<< orphan*/  g_zfshdl ; 
 int /*<<< orphan*/  zfs_unavail_pool ; 
 int /*<<< orphan*/  zpool_iter (int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 

__attribute__((used)) static void *
zfs_enum_pools(void *arg)
{
	(void) zpool_iter(g_zfshdl, zfs_unavail_pool, (void *)&g_pool_list);
	/*
	 * Linux - instead of using a thread pool, each list entry
	 * will spawn a thread when an unavailable pool transitions
	 * to available. zfs_slm_fini will wait for these threads.
	 */
	g_enumeration_done = B_TRUE;
	return (NULL);
}