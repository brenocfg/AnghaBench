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
struct window {int /*<<< orphan*/  options; } ;

/* Variables and functions */
 int WINDOW_ACTIVITY ; 
 int WINDOW_BELL ; 
 int WINDOW_SILENCE ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int
alerts_enabled(struct window *w, int flags)
{
	if (flags & WINDOW_BELL) {
		if (options_get_number(w->options, "monitor-bell"))
			return (1);
	}
	if (flags & WINDOW_ACTIVITY) {
		if (options_get_number(w->options, "monitor-activity"))
			return (1);
	}
	if (flags & WINDOW_SILENCE) {
		if (options_get_number(w->options, "monitor-silence") != 0)
			return (1);
	}
	return (0);
}