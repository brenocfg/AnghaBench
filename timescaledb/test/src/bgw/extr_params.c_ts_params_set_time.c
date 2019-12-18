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
typedef  int /*<<< orphan*/  int64 ;
struct TYPE_5__ {int /*<<< orphan*/  timer_latch; int /*<<< orphan*/  current_time; } ;
struct TYPE_6__ {TYPE_1__ params; int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ TestParamsWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SetLatch (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_close_wrapper (TYPE_2__*) ; 
 TYPE_2__* params_open_wrapper () ; 

void
ts_params_set_time(int64 new_val, bool set_latch)
{
	TestParamsWrapper *wrapper = params_open_wrapper();

	Assert(wrapper != NULL);

	SpinLockAcquire(&wrapper->mutex);
	wrapper->params.current_time = new_val;
	SpinLockRelease(&wrapper->mutex);

	if (set_latch)
		SetLatch(&wrapper->params.timer_latch);

	params_close_wrapper(wrapper);
}