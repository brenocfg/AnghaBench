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
 int /*<<< orphan*/  B_FALSE ; 
 int ZFS_DEBUG_SET_ERROR ; 
 int /*<<< orphan*/  __dprintf (int /*<<< orphan*/ ,char const*,char const*,int,char*,int) ; 
 int zfs_flags ; 

void
__set_error(const char *file, const char *func, int line, int err)
{
	/*
	 * To enable this:
	 *
	 * $ echo 512 >/sys/module/zfs/parameters/zfs_flags
	 */
	if (zfs_flags & ZFS_DEBUG_SET_ERROR)
		__dprintf(B_FALSE, file, func, line, "error %lu", err);
}