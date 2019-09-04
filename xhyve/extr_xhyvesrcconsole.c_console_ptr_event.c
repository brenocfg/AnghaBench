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
typedef  int /*<<< orphan*/  uint8_t ;
struct TYPE_2__ {int /*<<< orphan*/  ptr_arg; int /*<<< orphan*/  (* ptr_event_cb ) (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ;} ;

/* Variables and functions */
 TYPE_1__ console ; 
 int /*<<< orphan*/  stub1 (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ) ; 

void
console_ptr_event(uint8_t button, int x, int y)
{
	if (console.ptr_event_cb)
		(*console.ptr_event_cb)(button, x, y, console.ptr_arg);
}