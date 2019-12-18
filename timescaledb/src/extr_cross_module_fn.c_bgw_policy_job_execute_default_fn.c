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
typedef  int /*<<< orphan*/  BgwJob ;

/* Variables and functions */
 int /*<<< orphan*/  error_no_default_fn_enterprise () ; 
 int /*<<< orphan*/  pg_unreachable () ; 

__attribute__((used)) static bool
bgw_policy_job_execute_default_fn(BgwJob *job)
{
	error_no_default_fn_enterprise();
	pg_unreachable();
}