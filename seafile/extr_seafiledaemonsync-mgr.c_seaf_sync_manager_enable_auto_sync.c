#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_8__ {int /*<<< orphan*/  started; } ;
struct TYPE_7__ {TYPE_1__* priv; } ;
struct TYPE_6__ {int /*<<< orphan*/  auto_sync_enabled; } ;
typedef  TYPE_2__ SeafSyncManager ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  enable_auto_sync_for_repos (TYPE_2__*) ; 
 int /*<<< orphan*/  g_debug (char*) ; 
 TYPE_4__* seaf ; 
 int /*<<< orphan*/  seaf_message (char*) ; 

int
seaf_sync_manager_enable_auto_sync (SeafSyncManager *mgr)
{
    if (!seaf->started) {
        seaf_message ("sync manager is not started, skip enable auto sync.\n");
        return -1;
    }

    enable_auto_sync_for_repos (mgr);

    mgr->priv->auto_sync_enabled = TRUE;
    g_debug ("[sync mgr] auto sync is enabled\n");
    return 0;
}