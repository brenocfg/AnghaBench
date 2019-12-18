#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ z_flags; } ;
struct TYPE_4__ {int /*<<< orphan*/  z_fuid; TYPE_1__ z_hdr; } ;
typedef  TYPE_2__ zfs_ace_t ;
typedef  int /*<<< orphan*/  uint64_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ ACE_EVERYONE ; 
 scalar_t__ ACE_OWNER ; 
 scalar_t__ ACE_TYPE_FLAGS ; 
 scalar_t__ OWNING_GROUP ; 

__attribute__((used)) static void
zfs_ace_fuid_set_who(void *arg, uint64_t who)
{
	zfs_ace_t *acep = arg;

	uint16_t entry_type = acep->z_hdr.z_flags & ACE_TYPE_FLAGS;

	if (entry_type == ACE_OWNER || entry_type == OWNING_GROUP ||
	    entry_type == ACE_EVERYONE)
		return;
	acep->z_fuid = who;
}