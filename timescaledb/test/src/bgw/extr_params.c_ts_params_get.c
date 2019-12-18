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
struct TYPE_4__ {int /*<<< orphan*/  mutex; int /*<<< orphan*/  params; } ;
typedef  TYPE_1__ TestParamsWrapper ;
typedef  int /*<<< orphan*/  TestParams ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SpinLockAcquire (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SpinLockRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * palloc (int) ; 
 int /*<<< orphan*/  params_close_wrapper (TYPE_1__*) ; 
 TYPE_1__* params_open_wrapper () ; 

TestParams *
ts_params_get()
{
	TestParamsWrapper *wrapper = params_open_wrapper();
	TestParams *res;

	Assert(wrapper != NULL);

	res = palloc(sizeof(TestParams));

	SpinLockAcquire(&wrapper->mutex);

	memcpy(res, &wrapper->params, sizeof(TestParams));

	SpinLockRelease(&wrapper->mutex);

	params_close_wrapper(wrapper);

	return res;
}