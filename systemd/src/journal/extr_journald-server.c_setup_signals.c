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
struct TYPE_5__ {int /*<<< orphan*/  sigrtmin1_event_source; int /*<<< orphan*/  event; int /*<<< orphan*/  sigint_event_source; int /*<<< orphan*/  sigterm_event_source; int /*<<< orphan*/  sigusr2_event_source; int /*<<< orphan*/  sigusr1_event_source; } ;
typedef  TYPE_1__ Server ;

/* Variables and functions */
 scalar_t__ SD_EVENT_PRIORITY_NORMAL ; 
 scalar_t__ SIGINT ; 
 scalar_t__ SIGRTMIN ; 
 scalar_t__ SIGTERM ; 
 scalar_t__ SIGUSR1 ; 
 scalar_t__ SIGUSR2 ; 
 int /*<<< orphan*/  SIG_SETMASK ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  dispatch_sigrtmin1 ; 
 int /*<<< orphan*/  dispatch_sigterm ; 
 int /*<<< orphan*/  dispatch_sigusr1 ; 
 int /*<<< orphan*/  dispatch_sigusr2 ; 
 int sd_event_add_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ,TYPE_1__*) ; 
 int sd_event_source_set_priority (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ sigprocmask_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,scalar_t__,scalar_t__,scalar_t__,scalar_t__,int) ; 

__attribute__((used)) static int setup_signals(Server *s) {
        int r;

        assert(s);

        assert_se(sigprocmask_many(SIG_SETMASK, NULL, SIGINT, SIGTERM, SIGUSR1, SIGUSR2, SIGRTMIN+1, -1) >= 0);

        r = sd_event_add_signal(s->event, &s->sigusr1_event_source, SIGUSR1, dispatch_sigusr1, s);
        if (r < 0)
                return r;

        r = sd_event_add_signal(s->event, &s->sigusr2_event_source, SIGUSR2, dispatch_sigusr2, s);
        if (r < 0)
                return r;

        r = sd_event_add_signal(s->event, &s->sigterm_event_source, SIGTERM, dispatch_sigterm, s);
        if (r < 0)
                return r;

        /* Let's process SIGTERM late, so that we flush all queued messages to disk before we exit */
        r = sd_event_source_set_priority(s->sigterm_event_source, SD_EVENT_PRIORITY_NORMAL+20);
        if (r < 0)
                return r;

        /* When journald is invoked on the terminal (when debugging), it's useful if C-c is handled
         * equivalent to SIGTERM. */
        r = sd_event_add_signal(s->event, &s->sigint_event_source, SIGINT, dispatch_sigterm, s);
        if (r < 0)
                return r;

        r = sd_event_source_set_priority(s->sigint_event_source, SD_EVENT_PRIORITY_NORMAL+20);
        if (r < 0)
                return r;

        /* SIGRTMIN+1 causes an immediate sync. We process this very late, so that everything else queued at
         * this point is really written to disk. Clients can watch /run/systemd/journal/synced with inotify
         * until its mtime changes to see when a sync happened. */
        r = sd_event_add_signal(s->event, &s->sigrtmin1_event_source, SIGRTMIN+1, dispatch_sigrtmin1, s);
        if (r < 0)
                return r;

        r = sd_event_source_set_priority(s->sigrtmin1_event_source, SD_EVENT_PRIORITY_NORMAL+15);
        if (r < 0)
                return r;

        return 0;
}