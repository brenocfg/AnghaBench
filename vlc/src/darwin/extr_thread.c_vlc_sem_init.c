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
typedef  int /*<<< orphan*/  vlc_sem_t ;

/* Variables and functions */
 scalar_t__ KERN_SUCCESS ; 
 int /*<<< orphan*/  SYNC_POLICY_FIFO ; 
 int /*<<< orphan*/  abort () ; 
 int /*<<< orphan*/  mach_task_self () ; 
 scalar_t__ semaphore_create (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned int) ; 
 scalar_t__ unlikely (int) ; 

void vlc_sem_init (vlc_sem_t *sem, unsigned value)
{
    if (unlikely(semaphore_create(mach_task_self(), sem, SYNC_POLICY_FIFO, value) != KERN_SUCCESS))
        abort ();
}