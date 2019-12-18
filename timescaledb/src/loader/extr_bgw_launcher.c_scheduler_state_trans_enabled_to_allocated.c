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
struct TYPE_5__ {scalar_t__ state; int /*<<< orphan*/ * db_scheduler_handle; } ;
typedef  TYPE_1__ DbHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ALLOCATED ; 
 int /*<<< orphan*/  Assert (int) ; 
 scalar_t__ ENABLED ; 
 int /*<<< orphan*/  report_bgw_limit_exceeded (TYPE_1__*) ; 
 int /*<<< orphan*/  scheduler_modify_state (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_bgw_total_workers_increment () ; 

__attribute__((used)) static void
scheduler_state_trans_enabled_to_allocated(DbHashEntry *entry)
{
	Assert(entry->state == ENABLED);
	Assert(entry->db_scheduler_handle == NULL);
	/* Reserve a spot for this scheduler with BGW counter */
	if (!ts_bgw_total_workers_increment())
	{
		report_bgw_limit_exceeded(entry);
		return;
	}
	scheduler_modify_state(entry, ALLOCATED);
}