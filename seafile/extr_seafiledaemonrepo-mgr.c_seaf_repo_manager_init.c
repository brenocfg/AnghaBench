#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_5__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  cevent_handler ;
struct TYPE_11__ {int /*<<< orphan*/  ev_mgr; } ;
struct TYPE_10__ {TYPE_2__* seaf; TYPE_1__* priv; int /*<<< orphan*/  index_dir; } ;
struct TYPE_9__ {int /*<<< orphan*/  seaf_dir; } ;
struct TYPE_8__ {int /*<<< orphan*/  cevent_id; } ;
typedef  TYPE_3__ SeafRepoManager ;

/* Variables and functions */
 int /*<<< orphan*/  cevent_manager_register (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ checkdir_with_mkdir (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_folder_perms (TYPE_3__*) ; 
 int /*<<< orphan*/  load_repos (TYPE_3__*,int /*<<< orphan*/ ) ; 
 scalar_t__ notify_sync_error ; 
 TYPE_5__* seaf ; 
 int /*<<< orphan*/  seaf_warning (char*,int /*<<< orphan*/ ) ; 

int
seaf_repo_manager_init (SeafRepoManager *mgr)
{
    if (checkdir_with_mkdir (mgr->index_dir) < 0) {
        seaf_warning ("Index dir %s does not exist and is unable to create\n",
                   mgr->index_dir);
        return -1;
    }

    mgr->priv->cevent_id = cevent_manager_register (seaf->ev_mgr,
                                                    (cevent_handler)notify_sync_error,
                                                    NULL);

    /* Load all the repos into memory on the client side. */
    load_repos (mgr, mgr->seaf->seaf_dir);

    /* Load folder permissions from db. */
    init_folder_perms (mgr);

    return 0;
}