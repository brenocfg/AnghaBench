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
struct TYPE_3__ {int /*<<< orphan*/  http_server_states; } ;
typedef  TYPE_1__ SeafSyncManager ;

/* Variables and functions */
 int G_USEC_PER_SEC ; 
 int /*<<< orphan*/  g_hash_table_foreach (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  g_usleep (int) ; 
 int /*<<< orphan*/  update_head_commit_ids_for_server ; 

__attribute__((used)) static void *
update_cached_head_commit_ids (void *arg)
{
    SeafSyncManager *mgr = (SeafSyncManager *)arg;

    while (1) {
        g_usleep (30 * G_USEC_PER_SEC);

        g_hash_table_foreach (mgr->http_server_states, update_head_commit_ids_for_server, mgr);
    }

    return NULL;
}