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
struct TYPE_5__ {scalar_t__ nscd_cache_flush_event; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  on_nscd_cache_flush_event ; 
 int sd_event_add_defer (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (scalar_t__,char*) ; 
 int sd_event_source_set_enabled (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_unref (scalar_t__) ; 

int manager_enqueue_nscd_cache_flush(Manager *m) {
        int r;

        assert(m);

        if (!m->nscd_cache_flush_event) {
                r = sd_event_add_defer(m->event, &m->nscd_cache_flush_event, on_nscd_cache_flush_event, m);
                if (r < 0)
                        return log_error_errno(r, "Failed to allocate NSCD cache flush event: %m");

                sd_event_source_set_description(m->nscd_cache_flush_event, "nscd-cache-flush");
        }

        r = sd_event_source_set_enabled(m->nscd_cache_flush_event, SD_EVENT_ONESHOT);
        if (r < 0) {
                m->nscd_cache_flush_event = sd_event_source_unref(m->nscd_cache_flush_event);
                return log_error_errno(r, "Failed to enable NSCD cache flush event: %m");
        }

        return 0;
}