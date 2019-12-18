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
struct group_info {int ngroups; } ;
struct TYPE_3__ {struct group_info* group_info; } ;
typedef  TYPE_1__ cred_t ;

/* Variables and functions */
 int NGROUPS_PER_BLOCK ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 

int
crgetngroups(const cred_t *cr)
{
	struct group_info *gi;
	int rc;

	gi = cr->group_info;
	rc = gi->ngroups;
#ifndef HAVE_GROUP_INFO_GID
	/*
	 * For Linux <= 4.8,
	 * crgetgroups will only returns gi->blocks[0], which contains only
	 * the first NGROUPS_PER_BLOCK groups.
	 */
	if (rc > NGROUPS_PER_BLOCK) {
		WARN_ON_ONCE(1);
		rc = NGROUPS_PER_BLOCK;
	}
#endif
	return (rc);
}