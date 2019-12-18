#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  event; } ;
typedef  TYPE_1__ RunContext ;
typedef  int /*<<< orphan*/  PTYForward ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_FAILURE ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ *) ; 
 int log_error_errno (int,char*) ; 
 int /*<<< orphan*/  run_context_check_done (TYPE_1__*) ; 
 int /*<<< orphan*/  sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pty_forward_handler(PTYForward *f, int rcode, void *userdata) {
        RunContext *c = userdata;

        assert(f);

        if (rcode < 0) {
                sd_event_exit(c->event, EXIT_FAILURE);
                return log_error_errno(rcode, "Error on PTY forwarding logic: %m");
        }

        run_context_check_done(c);
        return 0;
}