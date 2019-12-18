#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ total_workers; int /*<<< orphan*/  mutex; } ;
typedef  int /*<<< orphan*/  CounterState ;

/* Variables and functions */
 int /*<<< orphan*/  AddinShmemInitLock ; 
 int /*<<< orphan*/  BGW_COUNTER_STATE_NAME ; 
 int /*<<< orphan*/  LWLockAcquire (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LWLockRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LW_EXCLUSIVE ; 
 TYPE_1__* ShmemInitStruct (int /*<<< orphan*/ ,int,int*) ; 
 int /*<<< orphan*/  SpinLockInit (int /*<<< orphan*/ *) ; 
 TYPE_1__* ct ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
bgw_counter_state_init()
{
	bool found;

	LWLockAcquire(AddinShmemInitLock, LW_EXCLUSIVE);
	ct = ShmemInitStruct(BGW_COUNTER_STATE_NAME, sizeof(CounterState), &found);
	if (!found)
	{
		memset(ct, 0, sizeof(CounterState));
		SpinLockInit(&ct->mutex);
		ct->total_workers = 0;
	}
	LWLockRelease(AddinShmemInitLock);
}