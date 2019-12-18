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
typedef  int /*<<< orphan*/  siginfo_t ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 void* INT_TO_PTR (float) ; 
 int /*<<< orphan*/  PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_exit (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sd_event_source_get_event (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_event_source_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int child_handler(sd_event_source *s, const siginfo_t *si, void *userdata) {

        assert_se(s);
        assert_se(si);

        log_info("got child on %c", PTR_TO_INT(userdata));

        assert_se(userdata == INT_TO_PTR('f'));

        assert_se(sd_event_exit(sd_event_source_get_event(s), 0) >= 0);
        sd_event_source_unref(s);

        return 1;
}