#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {struct super_block* z_sb; } ;
typedef  TYPE_1__ zfsvfs_t ;
typedef  scalar_t__ uint64_t ;
struct super_block {int /*<<< orphan*/  s_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  SB_NOATIME ; 

__attribute__((used)) static void
atime_changed_cb(void *arg, uint64_t newval)
{
	zfsvfs_t *zfsvfs = arg;
	struct super_block *sb = zfsvfs->z_sb;

	if (sb == NULL)
		return;
	/*
	 * Update SB_NOATIME bit in VFS super block.  Since atime update is
	 * determined by atime_needs_update(), atime_needs_update() needs to
	 * return false if atime is turned off, and not unconditionally return
	 * false if atime is turned on.
	 */
	if (newval)
		sb->s_flags &= ~SB_NOATIME;
	else
		sb->s_flags |= SB_NOATIME;
}