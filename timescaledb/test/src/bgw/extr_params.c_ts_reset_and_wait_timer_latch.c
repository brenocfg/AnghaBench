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
struct TYPE_5__ {int /*<<< orphan*/  timer_latch; } ;
struct TYPE_6__ {TYPE_1__ params; } ;
typedef  TYPE_2__ TestParamsWrapper ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ *) ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_TIMEOUT ; 
 int /*<<< orphan*/  WaitLatchCompat (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  params_close_wrapper (TYPE_2__*) ; 
 TYPE_2__* params_open_wrapper () ; 

void
ts_reset_and_wait_timer_latch()
{
	TestParamsWrapper *wrapper = params_open_wrapper();

	Assert(wrapper != NULL);

	ResetLatch(&wrapper->params.timer_latch);
	WaitLatchCompat(&wrapper->params.timer_latch,
					WL_LATCH_SET | WL_TIMEOUT | WL_POSTMASTER_DEATH,
					10000);

	params_close_wrapper(wrapper);
}