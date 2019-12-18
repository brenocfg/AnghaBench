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
struct window {struct window* name; int /*<<< orphan*/  options; int /*<<< orphan*/  offset_timer; int /*<<< orphan*/  alerts_timer; int /*<<< orphan*/  name_event; struct window* old_layout; int /*<<< orphan*/ * saved_layout_root; int /*<<< orphan*/ * layout_root; int /*<<< orphan*/  references; int /*<<< orphan*/  id; } ;

/* Variables and functions */
 int /*<<< orphan*/  RB_REMOVE (int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct window*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 scalar_t__ event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (struct window*) ; 
 int /*<<< orphan*/  layout_free_cell (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  options_free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  window_destroy_panes (struct window*) ; 
 int /*<<< orphan*/  windows ; 

__attribute__((used)) static void
window_destroy(struct window *w)
{
	log_debug("window @%u destroyed (%d references)", w->id, w->references);

	RB_REMOVE(windows, &windows, w);

	if (w->layout_root != NULL)
		layout_free_cell(w->layout_root);
	if (w->saved_layout_root != NULL)
		layout_free_cell(w->saved_layout_root);
	free(w->old_layout);

	window_destroy_panes(w);

	if (event_initialized(&w->name_event))
		evtimer_del(&w->name_event);

	if (event_initialized(&w->alerts_timer))
		evtimer_del(&w->alerts_timer);
	if (event_initialized(&w->offset_timer))
		event_del(&w->offset_timer);

	options_free(w->options);

	free(w->name);
	free(w);
}