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
struct timer_node {struct timer_node* next; } ;
struct timer_event {int /*<<< orphan*/  handle; int /*<<< orphan*/  session; } ;
struct skynet_message {size_t sz; int /*<<< orphan*/ * data; int /*<<< orphan*/  session; scalar_t__ source; } ;

/* Variables and functions */
 size_t MESSAGE_TYPE_SHIFT ; 
 scalar_t__ PTYPE_RESPONSE ; 
 int /*<<< orphan*/  skynet_context_push (int /*<<< orphan*/ ,struct skynet_message*) ; 
 int /*<<< orphan*/  skynet_free (struct timer_node*) ; 

__attribute__((used)) static inline void
dispatch_list(struct timer_node *current) {
	do {
		struct timer_event * event = (struct timer_event *)(current+1);
		struct skynet_message message;
		message.source = 0;
		message.session = event->session;
		message.data = NULL;
		message.sz = (size_t)PTYPE_RESPONSE << MESSAGE_TYPE_SHIFT;

		skynet_context_push(event->handle, &message);
		
		struct timer_node * temp = current;
		current=current->next;
		skynet_free(temp);	
	} while (current);
}