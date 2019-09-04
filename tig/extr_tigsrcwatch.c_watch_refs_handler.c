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
struct watch_handler {int dummy; } ;
typedef  enum watch_trigger { ____Placeholder_watch_trigger } watch_trigger ;
typedef  enum watch_event { ____Placeholder_watch_event } watch_event ;

/* Variables and functions */
 int WATCH_EVENT_AFTER_COMMAND ; 
 int WATCH_NONE ; 
 int /*<<< orphan*/  load_refs (int) ; 

__attribute__((used)) static enum watch_trigger
watch_refs_handler(struct watch_handler *handler, enum watch_event event,
		   enum watch_trigger check)
{
	if (event == WATCH_EVENT_AFTER_COMMAND)
		load_refs(true);

	return WATCH_NONE;
}