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
struct watch {int /*<<< orphan*/  changed; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;
typedef  enum watch_event { ____Placeholder_watch_event } watch_event ;

/* Variables and functions */
 int watch_unchanged_triggers (struct watch*) ; 
 int watch_update_event (int,int,int /*<<< orphan*/ ) ; 

enum watch_trigger
watch_update_single(struct watch *watch, enum watch_event event)
{
	enum watch_trigger trigger = watch_unchanged_triggers(watch);

	return watch_update_event(event, trigger, watch->changed);
}