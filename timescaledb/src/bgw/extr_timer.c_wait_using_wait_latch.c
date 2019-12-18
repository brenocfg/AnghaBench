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
typedef  scalar_t__ int64 ;
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  Assert (int /*<<< orphan*/ ) ; 
 scalar_t__ INT_MAX ; 
 scalar_t__ MAX_TIMEOUT ; 
 int /*<<< orphan*/  MyLatch ; 
 int /*<<< orphan*/  ResetLatch (int /*<<< orphan*/ ) ; 
 int WL_LATCH_SET ; 
 int WL_POSTMASTER_DEATH ; 
 int WL_TIMEOUT ; 
 int WaitLatchCompat (int /*<<< orphan*/ ,int,scalar_t__) ; 
 scalar_t__ get_timeout_millisec (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  on_postmaster_death () ; 

__attribute__((used)) static bool
wait_using_wait_latch(TimestampTz until)
{
	int wl_rc;

	int64 timeout = get_timeout_millisec(until);

	Assert(timeout >= 0 && "get_timeout_millisec underflow");

	if (timeout > MAX_TIMEOUT)
		timeout = MAX_TIMEOUT;

	/* Wait latch requires timeout to be <= INT_MAX */
	if ((int64) timeout > (int64) INT_MAX)
		timeout = INT_MAX;

	wl_rc = WaitLatchCompat(MyLatch, WL_LATCH_SET | WL_TIMEOUT | WL_POSTMASTER_DEATH, timeout);
	ResetLatch(MyLatch);
	if (wl_rc & WL_POSTMASTER_DEATH)
		on_postmaster_death();

	return true;
}