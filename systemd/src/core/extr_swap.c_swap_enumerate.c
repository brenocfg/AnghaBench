#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {int /*<<< orphan*/  swap_event_source; scalar_t__ proc_swaps; int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 scalar_t__ ENOENT ; 
 int /*<<< orphan*/  EPOLLPRI ; 
 scalar_t__ SD_EVENT_PRIORITY_NORMAL ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fileno (scalar_t__) ; 
 scalar_t__ fopen (char*,char*) ; 
 int /*<<< orphan*/  log_debug_errno (scalar_t__,char*) ; 
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  log_warning_errno (scalar_t__,char*) ; 
 int sd_event_add_io (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_source_set_description (int /*<<< orphan*/ ,char*) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  swap_dispatch_io ; 
 int swap_load_proc_swaps (TYPE_1__*,int) ; 
 int /*<<< orphan*/  swap_shutdown (TYPE_1__*) ; 

__attribute__((used)) static void swap_enumerate(Manager *m) {
        int r;

        assert(m);

        if (!m->proc_swaps) {
                m->proc_swaps = fopen("/proc/swaps", "re");
                if (!m->proc_swaps) {
                        if (errno == ENOENT)
                                log_debug_errno(errno, "Not swap enabled, skipping enumeration.");
                        else
                                log_warning_errno(errno, "Failed to open /proc/swaps, ignoring: %m");

                        return;
                }

                r = sd_event_add_io(m->event, &m->swap_event_source, fileno(m->proc_swaps), EPOLLPRI, swap_dispatch_io, m);
                if (r < 0) {
                        log_error_errno(r, "Failed to watch /proc/swaps: %m");
                        goto fail;
                }

                /* Dispatch this before we dispatch SIGCHLD, so that
                 * we always get the events from /proc/swaps before
                 * the SIGCHLD of /sbin/swapon. */
                r = sd_event_source_set_priority(m->swap_event_source, SD_EVENT_PRIORITY_NORMAL-10);
                if (r < 0) {
                        log_error_errno(r, "Failed to change /proc/swaps priority: %m");
                        goto fail;
                }

                (void) sd_event_source_set_description(m->swap_event_source, "swap-proc");
        }

        r = swap_load_proc_swaps(m, false);
        if (r < 0)
                goto fail;

        return;

fail:
        swap_shutdown(m);
}