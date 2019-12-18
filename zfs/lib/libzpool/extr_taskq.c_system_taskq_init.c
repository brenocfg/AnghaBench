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
 int TASKQ_DYNAMIC ; 
 int TASKQ_PREPOPULATE ; 
 int /*<<< orphan*/  maxclsyspri ; 
 void* system_delay_taskq ; 
 void* system_taskq ; 
 void* taskq_create (char*,int,int /*<<< orphan*/ ,int,int,int) ; 

void
system_taskq_init(void)
{
	system_taskq = taskq_create("system_taskq", 64, maxclsyspri, 4, 512,
	    TASKQ_DYNAMIC | TASKQ_PREPOPULATE);
	system_delay_taskq = taskq_create("delay_taskq", 4, maxclsyspri, 4,
	    512, TASKQ_DYNAMIC | TASKQ_PREPOPULATE);
}