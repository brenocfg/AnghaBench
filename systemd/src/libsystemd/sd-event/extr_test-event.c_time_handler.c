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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 void* INT_TO_PTR (char) ; 
 int /*<<< orphan*/  PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  defer_handler ; 
 scalar_t__ do_quit ; 
 int got_c ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_add_defer (int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ,void*) ; 
 int /*<<< orphan*/  sd_event_source_get_event (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int time_handler(sd_event_source *s, uint64_t usec, void *userdata) {
        log_info("got timer on %c", PTR_TO_INT(userdata));

        if (userdata == INT_TO_PTR('c')) {

                if (do_quit) {
                        sd_event_source *p;

                        assert_se(sd_event_add_defer(sd_event_source_get_event(s), &p, defer_handler, INT_TO_PTR('d')) >= 0);
                        assert_se(sd_event_source_set_enabled(p, SD_EVENT_ONESHOT) >= 0);
                } else {
                        assert_se(!got_c);
                        got_c = true;
                }
        } else
                assert_not_reached("Huh?");

        return 2;
}