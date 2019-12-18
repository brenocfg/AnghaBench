#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int state; int /*<<< orphan*/  db_scheduler_handle; } ;
typedef  TYPE_1__ DbHashEntry ;

/* Variables and functions */
#define  ALLOCATED 131 
 int /*<<< orphan*/  BGWH_STOPPED ; 
#define  DISABLED 130 
#define  ENABLED 129 
#define  STARTED 128 
 int /*<<< orphan*/  get_background_worker_pid (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  scheduler_state_trans_allocated_to_started (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_state_trans_enabled_to_allocated (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_state_trans_started_to_disabled (TYPE_1__*) ; 

__attribute__((used)) static void
scheduler_state_trans_automatic(DbHashEntry *entry)
{
	switch (entry->state)
	{
		case ENABLED:
			scheduler_state_trans_enabled_to_allocated(entry);
			if (entry->state == ALLOCATED)
				scheduler_state_trans_allocated_to_started(entry);
			break;
		case ALLOCATED:
			scheduler_state_trans_allocated_to_started(entry);
			break;
		case STARTED:
			if (get_background_worker_pid(entry->db_scheduler_handle, NULL) == BGWH_STOPPED)
				scheduler_state_trans_started_to_disabled(entry);
			break;
		case DISABLED:
			break;
	}
}