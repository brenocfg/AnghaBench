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
 int /*<<< orphan*/  CommitTransactionCommand () ; 
 int /*<<< orphan*/  ERROR ; 
 int /*<<< orphan*/  StartTransactionCommand () ; 
 int /*<<< orphan*/  WARNING ; 
 int /*<<< orphan*/  elog (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static bool
test_job_2_error()
{
	StartTransactionCommand();
	elog(WARNING, "Before error job 2");

	elog(ERROR, "Error job 2");

	elog(WARNING, "After error job 2");

	CommitTransactionCommand();
	return true;
}