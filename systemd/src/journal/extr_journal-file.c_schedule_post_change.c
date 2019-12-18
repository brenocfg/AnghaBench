#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint64_t ;
struct TYPE_9__ {struct TYPE_9__* post_change_timer; scalar_t__ post_change_timer_period; } ;
typedef  TYPE_1__ JournalFile ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  journal_file_post_change (TYPE_1__*) ; 
 int /*<<< orphan*/  log_debug_errno (int,char*) ; 
 int sd_event_now (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*) ; 
 int sd_event_source_get_enabled (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_event_source_get_event (TYPE_1__*) ; 
 int sd_event_source_set_enabled (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int sd_event_source_set_time (TYPE_1__*,scalar_t__) ; 

__attribute__((used)) static void schedule_post_change(JournalFile *f) {
        uint64_t now;
        int r;

        assert(f);
        assert(f->post_change_timer);

        r = sd_event_source_get_enabled(f->post_change_timer, NULL);
        if (r < 0) {
                log_debug_errno(r, "Failed to get ftruncate timer state: %m");
                goto fail;
        }
        if (r > 0)
                return;

        r = sd_event_now(sd_event_source_get_event(f->post_change_timer), CLOCK_MONOTONIC, &now);
        if (r < 0) {
                log_debug_errno(r, "Failed to get clock's now for scheduling ftruncate: %m");
                goto fail;
        }

        r = sd_event_source_set_time(f->post_change_timer, now + f->post_change_timer_period);
        if (r < 0) {
                log_debug_errno(r, "Failed to set time for scheduling ftruncate: %m");
                goto fail;
        }

        r = sd_event_source_set_enabled(f->post_change_timer, SD_EVENT_ONESHOT);
        if (r < 0) {
                log_debug_errno(r, "Failed to enable scheduled ftruncate: %m");
                goto fail;
        }

        return;

fail:
        /* On failure, let's simply post the change immediately. */
        journal_file_post_change(f);
}