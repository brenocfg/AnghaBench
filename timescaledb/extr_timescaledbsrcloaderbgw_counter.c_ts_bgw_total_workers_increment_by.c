#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int total_workers; int /*<<< orphan*/  mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 TYPE_1__* ct ; 
 int ts_guc_max_background_workers ; 

extern bool
ts_bgw_total_workers_increment_by(int increment_by)
{
	bool incremented = false;
	int max_workers = ts_guc_max_background_workers;

	SpinLockAcquire(&ct->mutex);
	if (ct->total_workers + increment_by <= max_workers)
	{
		ct->total_workers += increment_by;
		incremented = true;
	}
	SpinLockRelease(&ct->mutex);
	return incremented;
}