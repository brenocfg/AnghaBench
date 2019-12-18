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

/* Variables and functions */
 int /*<<< orphan*/  fletcher_4_fini () ; 
 int /*<<< orphan*/  icp_fini () ; 
 int /*<<< orphan*/  random_fini () ; 
 int /*<<< orphan*/  spa_fini () ; 
 int /*<<< orphan*/  system_taskq_fini () ; 

void
kernel_fini(void)
{
	fletcher_4_fini();
	spa_fini();

	icp_fini();
	system_taskq_fini();

	random_fini();
}