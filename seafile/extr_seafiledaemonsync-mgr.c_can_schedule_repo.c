#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int gboolean ;
struct TYPE_6__ {scalar_t__ last_sync_time; } ;
struct TYPE_5__ {int sync_interval; scalar_t__ n_running_tasks; } ;
typedef  TYPE_1__ SeafSyncManager ;
typedef  TYPE_2__ SeafRepo ;

/* Variables and functions */
 scalar_t__ MAX_RUNNING_SYNC_TASKS ; 
 scalar_t__ time (int /*<<< orphan*/ *) ; 

__attribute__((used)) static gboolean
can_schedule_repo (SeafSyncManager *manager, SeafRepo *repo)
{
    int now = (int)time(NULL);

    return ((repo->last_sync_time == 0 ||
             repo->last_sync_time < now - manager->sync_interval) &&
            manager->n_running_tasks < MAX_RUNNING_SYNC_TASKS);
}