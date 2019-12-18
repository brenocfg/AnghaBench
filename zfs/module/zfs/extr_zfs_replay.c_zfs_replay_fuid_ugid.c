#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {void* z_fuid_group; void* z_fuid_owner; } ;
typedef  TYPE_1__ zfs_fuid_info_t ;
typedef  void* uint64_t ;

/* Variables and functions */
 scalar_t__ IS_EPHEMERAL (void*) ; 

__attribute__((used)) static void
zfs_replay_fuid_ugid(zfs_fuid_info_t *fuid_infop, uint64_t uid, uint64_t gid)
{
	/*
	 * If owner or group are log specific FUIDs then slurp up
	 * domain information and build zfs_fuid_info_t
	 */
	if (IS_EPHEMERAL(uid))
		fuid_infop->z_fuid_owner = uid;

	if (IS_EPHEMERAL(gid))
		fuid_infop->z_fuid_group = gid;
}