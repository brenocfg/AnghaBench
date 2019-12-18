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
typedef  int /*<<< orphan*/  unknown_job_type_hook_type ;

/* Variables and functions */
 int /*<<< orphan*/  unknown_job_type_hook ; 

void
ts_bgw_job_set_unknown_job_type_hook(unknown_job_type_hook_type hook)
{
	unknown_job_type_hook = hook;
}