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
 int /*<<< orphan*/  mq ; 
 int /*<<< orphan*/  queue_shmem_cleanup (int /*<<< orphan*/ ) ; 

extern void
ts_bgw_message_queue_shmem_cleanup(void)
{
	queue_shmem_cleanup(mq);
}