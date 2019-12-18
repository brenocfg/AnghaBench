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
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  DirectFunctionCall1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Int64GetDatum (int) ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  pg_advisory_lock_int8 ; 

__attribute__((used)) static bool
test_job_5_lock()
{
	BackgroundWorkerBlockSignals();
	/* Use the default sig handlers */
	BackgroundWorkerUnblockSignals();

	elog(WARNING, "Before lock job 5");

	/* have to have a txn, otherwise can't kill the process */
	StartTransactionCommand();
	DirectFunctionCall1(pg_advisory_lock_int8, Int64GetDatum(1));
	CommitTransactionCommand();

	elog(WARNING, "After lock job 5");
	return true;
}