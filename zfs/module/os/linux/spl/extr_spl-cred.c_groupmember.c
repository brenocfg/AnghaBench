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
struct group_info {int dummy; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {struct group_info* group_info; } ;
typedef  TYPE_1__ cred_t ;

/* Variables and functions */
 int /*<<< orphan*/  SGID_TO_KGID (int /*<<< orphan*/ ) ; 
 int cr_groups_search (struct group_info*,int /*<<< orphan*/ ) ; 

int
groupmember(gid_t gid, const cred_t *cr)
{
	struct group_info *gi;
	int rc;

	gi = cr->group_info;
	rc = cr_groups_search(gi, SGID_TO_KGID(gid));

	return (rc);
}