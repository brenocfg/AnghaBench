#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  pid_t ;
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/  vxid; int /*<<< orphan*/ * db_scheduler_handle; int /*<<< orphan*/  db_oid; } ;
typedef  TYPE_1__ DbHashEntry ;

/* Variables and functions */
 scalar_t__ ALLOCATED ; 
 int /*<<< orphan*/  Assert (int) ; 
 int /*<<< orphan*/  STARTED ; 
 int /*<<< orphan*/  SetInvalidVirtualTransactionId (int /*<<< orphan*/ ) ; 
 int register_entrypoint_for_db (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  report_error_on_worker_register_failure (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_modify_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_for_background_worker_startup (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
scheduler_state_trans_allocated_to_started(DbHashEntry *entry)
{
	pid_t worker_pid;
	bool worker_registered;

	Assert(entry->state == ALLOCATED);
	Assert(entry->db_scheduler_handle == NULL);

	worker_registered =
		register_entrypoint_for_db(entry->db_oid, entry->vxid, &entry->db_scheduler_handle);

	if (!worker_registered)
	{
		report_error_on_worker_register_failure(entry);
		return;
	}
	wait_for_background_worker_startup(entry->db_scheduler_handle, &worker_pid);
	SetInvalidVirtualTransactionId(entry->vxid);
	scheduler_modify_state(entry, STARTED);
}