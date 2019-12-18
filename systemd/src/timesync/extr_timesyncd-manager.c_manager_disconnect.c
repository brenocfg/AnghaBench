#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {void* event_timeout; int /*<<< orphan*/  clock_watch_fd; void* event_clock_watch; void* event_timer; int /*<<< orphan*/  resolve_query; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  manager_listen_stop (TYPE_1__*) ; 
 int /*<<< orphan*/  safe_close (int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  sd_notifyf (int,char*) ; 
 int /*<<< orphan*/  sd_resolve_query_unref (int /*<<< orphan*/ ) ; 

void manager_disconnect(Manager *m) {
        assert(m);

        m->resolve_query = sd_resolve_query_unref(m->resolve_query);

        m->event_timer = sd_event_source_unref(m->event_timer);

        manager_listen_stop(m);

        m->event_clock_watch = sd_event_source_unref(m->event_clock_watch);
        m->clock_watch_fd = safe_close(m->clock_watch_fd);

        m->event_timeout = sd_event_source_unref(m->event_timeout);

        sd_notifyf(false, "STATUS=Idle.");
}