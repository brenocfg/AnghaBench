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
typedef  int /*<<< orphan*/  u_int ;
struct window {int /*<<< orphan*/  alerts_timer; int /*<<< orphan*/  id; int /*<<< orphan*/  options; int /*<<< orphan*/  flags; } ;
struct timeval {scalar_t__ tv_sec; } ;

/* Variables and functions */
 int /*<<< orphan*/  WINDOW_SILENCE ; 
 int /*<<< orphan*/  alerts_timer ; 
 int /*<<< orphan*/  event_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  event_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  event_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct window*) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 

__attribute__((used)) static void
alerts_reset(struct window *w)
{
	struct timeval	tv;

	if (!event_initialized(&w->alerts_timer))
		evtimer_set(&w->alerts_timer, alerts_timer, w);

	w->flags &= ~WINDOW_SILENCE;
	event_del(&w->alerts_timer);

	timerclear(&tv);
	tv.tv_sec = options_get_number(w->options, "monitor-silence");

	log_debug("@%u alerts timer reset %u", w->id, (u_int)tv.tv_sec);
	if (tv.tv_sec != 0)
		event_add(&w->alerts_timer, &tv);
}