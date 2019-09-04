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
struct TYPE_5__ {int /*<<< orphan*/  mock_wait_type; } ;
struct TYPE_6__ {int /*<<< orphan*/  mutex; TYPE_1__ params; } ;
typedef  TYPE_2__ TestParamsWrapper ;
typedef  int /*<<< orphan*/  MockWaitType ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  params_close_wrapper (TYPE_2__*) ; 
 TYPE_2__* params_open_wrapper () ; 

__attribute__((used)) static void
params_set_mock_wait_type(MockWaitType new_val)
{
	TestParamsWrapper *wrapper = params_open_wrapper();

	Assert(wrapper != NULL);

	SpinLockAcquire(&wrapper->mutex);

	wrapper->params.mock_wait_type = new_val;

	SpinLockRelease(&wrapper->mutex);

	params_close_wrapper(wrapper);
}