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
struct signalfd_siginfo {int dummy; } ;
typedef  int /*<<< orphan*/  sd_event_source ;
typedef  scalar_t__ pid_t ;

/* Variables and functions */
 int /*<<< orphan*/  EXIT_SUCCESS ; 
 void* INT_TO_PTR (float) ; 
 int /*<<< orphan*/  PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  SIGCHLD ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  WEXITED ; 
 int /*<<< orphan*/  _exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  child_handler ; 
 scalar_t__ fork () ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_add_child (int /*<<< orphan*/ ,int /*<<< orphan*/ **,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sd_event_source_get_event (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ *) ; 
 scalar_t__ sigprocmask_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int signal_handler(sd_event_source *s, const struct signalfd_siginfo *si, void *userdata) {
        sd_event_source *p = NULL;
        pid_t pid;

        assert_se(s);
        assert_se(si);

        log_info("got signal on %c", PTR_TO_INT(userdata));

        assert_se(userdata == INT_TO_PTR('e'));

        assert_se(sigprocmask_many(SIG_BLOCK, NULL, SIGCHLD, -1) >= 0);

        pid = fork();
        assert_se(pid >= 0);

        if (pid == 0)
                _exit(EXIT_SUCCESS);

        assert_se(sd_event_add_child(sd_event_source_get_event(s), &p, pid, WEXITED, child_handler, INT_TO_PTR('f')) >= 0);
        assert_se(sd_event_source_set_enabled(p, SD_EVENT_ONESHOT) >= 0);

        sd_event_source_unref(s);

        return 1;
}