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
struct TYPE_4__ {int /*<<< orphan*/  event; scalar_t__ forward; int /*<<< orphan*/  active_state; scalar_t__ match; } ;
typedef  TYPE_1__ RunContext ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 int STRPTR_IN_SET (int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int pty_forward_drain (scalar_t__) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void run_context_check_done(RunContext *c) {
        bool done;

        assert(c);

        if (c->match)
                done = STRPTR_IN_SET(c->active_state, "inactive", "failed");
        else
                done = true;

        if (c->forward && done) /* If the service is gone, it's time to drain the output */
                done = pty_forward_drain(c->forward);

        if (done)
                sd_event_exit(c->event, EXIT_SUCCESS);
}