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
struct watch {int triggers; int state; int changed; struct watch* next; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;
typedef  enum watch_event { ____Placeholder_watch_event } watch_event ;

/* Variables and functions */
 int WATCH_EVENT_AFTER_COMMAND ; 
 int WATCH_NONE ; 
 scalar_t__ watch_no_refresh (int) ; 
 struct watch* watches ; 

__attribute__((used)) static void
watch_apply_changes(struct watch *source, enum watch_event event,
		    enum watch_trigger changed)
{
	struct watch *watch;

	if (watch_no_refresh(event))
		return;

	for (watch = watches; watch; watch = watch->next) {
		enum watch_trigger triggers = changed & watch->triggers;

		if (source == watch) {
			source->state |= triggers;
			continue;
		}

		if (event == WATCH_EVENT_AFTER_COMMAND) {
			watch->state = WATCH_NONE;
			triggers = watch->triggers;
		}

		watch->changed |= triggers;
	}
}