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
typedef  int /*<<< orphan*/  time_t ;

/* Variables and functions */
 int /*<<< orphan*/  vm ; 
 int /*<<< orphan*/  vrtc_get_time (int /*<<< orphan*/ ) ; 

int
xh_vm_rtc_gettime(time_t *secs)
{
	*secs = vrtc_get_time(vm);
	return (0);
}