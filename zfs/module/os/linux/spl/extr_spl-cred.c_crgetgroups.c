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
struct group_info {scalar_t__ nblocks; int /*<<< orphan*/ * blocks; int /*<<< orphan*/  gid; } ;
typedef  int /*<<< orphan*/  gid_t ;
struct TYPE_3__ {struct group_info* group_info; } ;
typedef  TYPE_1__ cred_t ;

/* Variables and functions */
 int /*<<< orphan*/ * KGIDP_TO_SGIDP (int /*<<< orphan*/ ) ; 

gid_t *
crgetgroups(const cred_t *cr)
{
	struct group_info *gi;
	gid_t *gids = NULL;

	gi = cr->group_info;
#ifdef HAVE_GROUP_INFO_GID
	gids = KGIDP_TO_SGIDP(gi->gid);
#else
	if (gi->nblocks > 0)
		gids = KGIDP_TO_SGIDP(gi->blocks[0]);
#endif
	return (gids);
}