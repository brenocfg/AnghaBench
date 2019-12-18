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
typedef  int /*<<< orphan*/  uint32_t ;
struct timer_event {int session; int /*<<< orphan*/  handle; } ;
struct skynet_message {int session; size_t sz; int /*<<< orphan*/ * data; scalar_t__ source; } ;
typedef  int /*<<< orphan*/  event ;

/* Variables and functions */
 size_t MESSAGE_TYPE_SHIFT ; 
 scalar_t__ PTYPE_RESPONSE ; 
 int /*<<< orphan*/  TI ; 
 scalar_t__ skynet_context_push (int /*<<< orphan*/ ,struct skynet_message*) ; 
 int /*<<< orphan*/  timer_add (int /*<<< orphan*/ ,struct timer_event*,int,int) ; 

int
skynet_timeout(uint32_t handle, int time, int session) {
	if (time <= 0) {
		struct skynet_message message;
		message.source = 0;
		message.session = session;
		message.data = NULL;
		message.sz = (size_t)PTYPE_RESPONSE << MESSAGE_TYPE_SHIFT;

		if (skynet_context_push(handle, &message)) {
			return -1;
		}
	} else {
		struct timer_event event;
		event.handle = handle;
		event.session = session;
		timer_add(TI, &event, sizeof(event), time);
	}

	return session;
}