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
struct TYPE_3__ {scalar_t__ state_transition_failures; } ;
typedef  TYPE_1__ DbHashEntry ;

/* Variables and functions */
 int /*<<< orphan*/  ERRCODE_CONFIGURATION_LIMIT_EXCEEDED ; 
 int /*<<< orphan*/  LOG ; 
 int /*<<< orphan*/  ereport (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errcode (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errhint (char*) ; 
 int /*<<< orphan*/  errmsg (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ts_guc_max_background_workers ; 

__attribute__((used)) static void
report_bgw_limit_exceeded(DbHashEntry *entry)
{
	if (entry->state_transition_failures == 0)
		ereport(LOG,
				(errcode(ERRCODE_CONFIGURATION_LIMIT_EXCEEDED),
				 errmsg("TimescaleDB background worker limit of %d exceeded",
						ts_guc_max_background_workers),
				 errhint("Consider increasing timescaledb.max_background_workers.")));
	entry->state_transition_failures++;
}