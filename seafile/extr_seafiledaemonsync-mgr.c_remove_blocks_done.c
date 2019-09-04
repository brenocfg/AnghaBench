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
typedef  int /*<<< orphan*/  SyncTask ;

/* Variables and functions */
 int /*<<< orphan*/  SYNC_STATE_DONE ; 
 int /*<<< orphan*/  transition_sync_state (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
remove_blocks_done (void *vtask)
{
    SyncTask *task = vtask;

    transition_sync_state (task, SYNC_STATE_DONE);
}