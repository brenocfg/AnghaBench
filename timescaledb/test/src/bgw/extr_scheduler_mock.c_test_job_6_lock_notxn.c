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

/* Variables and functions */
 int /*<<< orphan*/  BackgroundWorkerBlockSignals () ; 
 int /*<<< orphan*/  BackgroundWorkerUnblockSignals () ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int) ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_advisory_lock_int8 ; 

__attribute__((used)) static bool
test_job_6_lock_notxn()
{
	BackgroundWorkerBlockSignals();
	/* Use the default sig handlers */
	BackgroundWorkerUnblockSignals();

	elog(WARNING, "Before lock job 6");

	/* no txn */
	DirectFunctionCall1(pg_advisory_lock_int8, Int64GetDatum(1));

	elog(WARNING, "After lock job 5");
	return true;
}