#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ptr_event_func_t ;
struct TYPE_2__ {int ptr_priority; void* ptr_arg; int /*<<< orphan*/  ptr_event_cb; } ;

/* Variables and functions */
 TYPE_1__ console ; 

void
console_ptr_register(ptr_event_func_t event_cb, void *arg, int pri)
{
	if (pri > console.ptr_priority) {
		console.ptr_event_cb = event_cb;
		console.ptr_arg = arg;
		console.ptr_priority = pri;
	}
}