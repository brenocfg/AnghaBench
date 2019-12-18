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
struct timeval {scalar_t__ tv_sec; scalar_t__ tv_usec; } ;
struct session {scalar_t__ attached; int /*<<< orphan*/  lock_timer; int /*<<< orphan*/  options; struct timeval activity_time; int /*<<< orphan*/  name; int /*<<< orphan*/  id; struct timeval last_activity_time; } ;

/* Variables and functions */
 int /*<<< orphan*/  evtimer_add (int /*<<< orphan*/ *,struct timeval*) ; 
 int /*<<< orphan*/  evtimer_del (int /*<<< orphan*/ *) ; 
 scalar_t__ evtimer_initialized (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  evtimer_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct session*) ; 
 int /*<<< orphan*/  gettimeofday (struct timeval*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,long long,int,long long,int) ; 
 int /*<<< orphan*/  memcpy (struct timeval*,struct timeval*,int) ; 
 scalar_t__ options_get_number (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  session_lock_timer ; 
 int /*<<< orphan*/  timerclear (struct timeval*) ; 

void
session_update_activity(struct session *s, struct timeval *from)
{
	struct timeval	*last = &s->last_activity_time;
	struct timeval	 tv;

	memcpy(last, &s->activity_time, sizeof *last);
	if (from == NULL)
		gettimeofday(&s->activity_time, NULL);
	else
		memcpy(&s->activity_time, from, sizeof s->activity_time);

	log_debug("session $%u %s activity %lld.%06d (last %lld.%06d)", s->id,
	    s->name, (long long)s->activity_time.tv_sec,
	    (int)s->activity_time.tv_usec, (long long)last->tv_sec,
	    (int)last->tv_usec);

	if (evtimer_initialized(&s->lock_timer))
		evtimer_del(&s->lock_timer);
	else
		evtimer_set(&s->lock_timer, session_lock_timer, s);

	if (s->attached != 0) {
		timerclear(&tv);
		tv.tv_sec = options_get_number(s->options, "lock-after-time");
		if (tv.tv_sec != 0)
			evtimer_add(&s->lock_timer, &tv);
	}
}