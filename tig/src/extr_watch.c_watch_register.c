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
struct watch {int triggers; void* state; void* changed; struct watch* next; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;

/* Variables and functions */
 void* WATCH_NONE ; 
 int /*<<< orphan*/  watch_unregister (struct watch*) ; 
 struct watch* watches ; 

void
watch_register(struct watch *watch, enum watch_trigger triggers)
{
	watch_unregister(watch);

	watch->next = watches;
	watches = watch;

	watch->triggers = triggers;
	watch->changed = WATCH_NONE;
	watch->state = WATCH_NONE;
}