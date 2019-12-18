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
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 void* INT_TO_PTR (char) ; 
 int /*<<< orphan*/  PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  SIGUSR1 ; 
 int /*<<< orphan*/  SIG_BLOCK ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  raise (int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_add_signal (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sd_event_source_get_event (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler ; 
 scalar_t__ sigprocmask_many (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int defer_handler(sd_event_source *s, void *userdata) {
        sd_event_source *p = NULL;

        assert_se(s);

        log_info("got defer on %c", PTR_TO_INT(userdata));

        assert_se(userdata == INT_TO_PTR('d'));

        assert_se(sigprocmask_many(SIG_BLOCK, NULL, SIGUSR1, -1) >= 0);

        assert_se(sd_event_add_signal(sd_event_source_get_event(s), &p, SIGUSR1, signal_handler, INT_TO_PTR('e')) >= 0);
        assert_se(sd_event_source_set_enabled(p, SD_EVENT_ONESHOT) >= 0);
        raise(SIGUSR1);

        sd_event_source_unref(s);

        return 1;
}