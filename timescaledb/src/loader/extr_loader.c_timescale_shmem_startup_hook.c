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
 int /*<<< orphan*/  prev_shmem_startup_hook () ; 
 int /*<<< orphan*/  ts_bgw_counter_shmem_startup () ; 
 int /*<<< orphan*/  ts_bgw_message_queue_shmem_startup () ; 
 int /*<<< orphan*/  ts_lwlocks_shmem_startup () ; 

__attribute__((used)) static void
timescale_shmem_startup_hook(void)
{
	if (prev_shmem_startup_hook)
		prev_shmem_startup_hook();
	ts_bgw_counter_shmem_startup();
	ts_bgw_message_queue_shmem_startup();
	ts_lwlocks_shmem_startup();
}