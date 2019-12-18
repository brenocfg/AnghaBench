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
typedef  int /*<<< orphan*/  TimestampTz ;

/* Variables and functions */
 int /*<<< orphan*/  error_no_default_fn_community () ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static TimestampTz
license_end_time_default_fn(void)
{
	error_no_default_fn_community();
	pg_unreachable();
}