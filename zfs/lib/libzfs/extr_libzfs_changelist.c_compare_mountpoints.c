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
 int /*<<< orphan*/  ZFS_PROP_MOUNTPOINT ; 
 int compare_props (void const*,void const*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
compare_mountpoints(const void *a, const void *b, void *unused)
{
	/*
	 * When unsharing or unmounting filesystems, we need to do it in
	 * mountpoint order.  This allows the user to have a mountpoint
	 * hierarchy that is different from the dataset hierarchy, and still
	 * allow it to be changed.
	 */
	return (compare_props(a, b, ZFS_PROP_MOUNTPOINT));
}