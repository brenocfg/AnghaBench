#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int shutdown_dry_run; int unlink_nologin; scalar_t__ scheduled_shutdown_timeout; int /*<<< orphan*/  scheduled_shutdown_type; void* nologin_timeout_source; void* wall_message_timeout_source; void* scheduled_shutdown_timeout_source; } ;
typedef  TYPE_1__ Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  mfree (int /*<<< orphan*/ ) ; 
 void* sd_event_source_unref (void*) ; 
 int /*<<< orphan*/  unlink (char*) ; 
 int /*<<< orphan*/  unlink_or_warn (char*) ; 

__attribute__((used)) static void reset_scheduled_shutdown(Manager *m) {
        assert(m);

        m->scheduled_shutdown_timeout_source = sd_event_source_unref(m->scheduled_shutdown_timeout_source);
        m->wall_message_timeout_source = sd_event_source_unref(m->wall_message_timeout_source);
        m->nologin_timeout_source = sd_event_source_unref(m->nologin_timeout_source);

        m->scheduled_shutdown_type = mfree(m->scheduled_shutdown_type);
        m->scheduled_shutdown_timeout = 0;
        m->shutdown_dry_run = false;

        if (m->unlink_nologin) {
                (void) unlink_or_warn("/run/nologin");
                m->unlink_nologin = false;
        }

        (void) unlink("/run/systemd/shutdown/scheduled");
}