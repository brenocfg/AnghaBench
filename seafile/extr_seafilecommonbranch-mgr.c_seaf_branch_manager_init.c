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
typedef  int /*<<< orphan*/  SeafBranchManager ;

/* Variables and functions */
 int open_db (int /*<<< orphan*/ *) ; 

int
seaf_branch_manager_init (SeafBranchManager *mgr)
{
#if defined( SEAFILE_SERVER ) && defined( FULL_FEATURE )
    mgr->priv->cevent_id = cevent_manager_register (seaf->ev_mgr,
                                    (cevent_handler)publish_repo_update_event,
                                                    NULL);
#endif    

    return open_db (mgr);
}