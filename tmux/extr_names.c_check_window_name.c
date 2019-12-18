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
struct window {int name; int /*<<< orphan*/  id; TYPE_1__* active; int /*<<< orphan*/  name_event; int /*<<< orphan*/  name_time; int /*<<< orphan*/  options; } ;
struct timeval {int tv_usec; } ;
struct TYPE_2__ {int flags; } ;

/* Variables and functions */
 int PANE_CHANGED ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_pending (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct window*) ; 
 char* format_window_name (struct window*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,struct timeval*,int) ; 
 int /*<<< orphan*/  name_time_callback ; 
 int name_time_expired (struct window*,struct timeval*) ; 
 int /*<<< orphan*/  options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  server_status_window (struct window*) ; 
 scalar_t__ strcmp (char*,int) ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 
 int /*<<< orphan*/  window_set_name (struct window*,char*) ; 

void
check_window_name(struct window *w)
{
	struct timeval	 tv, next;
	char		*name;
	int		 left;

	if (w->active == NULL)
		return;

	if (!options_get_number(w->options, "automatic-rename"))
		return;

	if (~w->active->flags & PANE_CHANGED) {
		log_debug("@%u active pane not changed", w->id);
		return;
	}
	log_debug("@%u active pane changed", w->id);

	gettimeofday(&tv, NULL);
	left = name_time_expired(w, &tv);
	if (left != 0) {
		if (!event_initialized(&w->name_event))
			evtimer_set(&w->name_event, name_time_callback, w);
		if (!evtimer_pending(&w->name_event, NULL)) {
			log_debug("@%u name timer queued (%d left)", w->id,
			    left);
			timerclear(&next);
			next.tv_usec = left;
			event_add(&w->name_event, &next);
		} else {
			log_debug("@%u name timer already queued (%d left)",
			    w->id, left);
		}
		return;
	}
	memcpy(&w->name_time, &tv, sizeof w->name_time);
	if (event_initialized(&w->name_event))
		evtimer_del(&w->name_event);

	w->active->flags &= ~PANE_CHANGED;

	name = format_window_name(w);
	if (strcmp(name, w->name) != 0) {
		log_debug("@%u new name %s (was %s)", w->id, name, w->name);
		window_set_name(w, name);
		server_status_window(w);
	} else
		log_debug("@%u name not changed (still %s)", w->id, w->name);

	free(name);
}