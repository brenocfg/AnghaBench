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
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  sd_event_source ;

/* Variables and functions */
 void* INT_TO_PTR (char) ; 
 int /*<<< orphan*/  PTR_TO_INT (void*) ; 
 int /*<<< orphan*/  SD_EVENT_OFF ; 
 int /*<<< orphan*/  SD_EVENT_ONESHOT ; 
 int /*<<< orphan*/  assert_not_reached (char*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int got_a ; 
 int got_b ; 
 int got_d ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ sd_event_source_set_enabled (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int io_handler(sd_event_source *s, int fd, uint32_t revents, void *userdata) {

        log_info("got IO on %c", PTR_TO_INT(userdata));

        if (userdata == INT_TO_PTR('a')) {
                assert_se(sd_event_source_set_enabled(s, SD_EVENT_OFF) >= 0);
                assert_se(!got_a);
                got_a = true;
        } else if (userdata == INT_TO_PTR('b')) {
                assert_se(!got_b);
                got_b = true;
        } else if (userdata == INT_TO_PTR('d')) {
                got_d++;
                if (got_d < 2)
                        assert_se(sd_event_source_set_enabled(s, SD_EVENT_ONESHOT) >= 0);
                else
                        assert_se(sd_event_source_set_enabled(s, SD_EVENT_OFF) >= 0);
        } else
                assert_not_reached("Yuck!");

        return 1;
}