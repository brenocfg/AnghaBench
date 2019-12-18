#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {int /*<<< orphan*/ * ev_mgr; } ;
struct TYPE_4__ {int /*<<< orphan*/  obj_store; } ;
typedef  TYPE_1__ SeafCommitManager ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_3__* seaf ; 
 scalar_t__ seaf_obj_store_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  seaf_warning (char*) ; 

int
seaf_commit_manager_init (SeafCommitManager *mgr)
{
#ifdef SEAFILE_SERVER

#ifdef FULL_FEATURE
    if (seaf_obj_store_init (mgr->obj_store, TRUE, seaf->ev_mgr) < 0) {
        seaf_warning ("[commit mgr] Failed to init commit object store.\n");
        return -1;
    }
#else
    if (seaf_obj_store_init (mgr->obj_store, FALSE, NULL) < 0) {
        seaf_warning ("[commit mgr] Failed to init commit object store.\n");
        return -1;
    }
#endif

#else
    if (seaf_obj_store_init (mgr->obj_store, TRUE, seaf->ev_mgr) < 0) {
        seaf_warning ("[commit mgr] Failed to init commit object store.\n");
        return -1;
    }
#endif

    return 0;
}