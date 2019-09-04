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
typedef  int int64 ;
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  GetCurrentTimestamp () ; 
 int MILLISECS_PER_SEC ; 
 scalar_t__ TIMESTAMP_IS_NOBEGIN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  TimestampDifference (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int*) ; 
 int USECS_PER_MILLISEC ; 

__attribute__((used)) static int64
get_timeout_millisec(TimestampTz by_time)
{
	int64 timeout_sec = 0;
	int timeout_usec = 0;

	if (TIMESTAMP_IS_NOBEGIN(by_time))
		return 0;

	TimestampDifference(GetCurrentTimestamp(), by_time, &timeout_sec, &timeout_usec);

	if (timeout_sec <= 0 && timeout_usec <= 0)
		return 0;

	return timeout_sec * MILLISECS_PER_SEC + timeout_usec / USECS_PER_MILLISEC;
}