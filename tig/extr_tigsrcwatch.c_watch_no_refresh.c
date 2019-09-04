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
typedef  enum watch_event { ____Placeholder_watch_event } watch_event ;

/* Variables and functions */
 scalar_t__ REFRESH_MODE_AFTER_COMMAND ; 
 scalar_t__ REFRESH_MODE_MANUAL ; 
 int WATCH_EVENT_AFTER_COMMAND ; 
 scalar_t__ opt_refresh_mode ; 

__attribute__((used)) static bool
watch_no_refresh(enum watch_event event)
{
	return opt_refresh_mode == REFRESH_MODE_MANUAL ||
	       (opt_refresh_mode == REFRESH_MODE_AFTER_COMMAND &&
		event != WATCH_EVENT_AFTER_COMMAND);
}