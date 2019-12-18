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
typedef  scalar_t__ usec_t ;
typedef  scalar_t__ uint64_t ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
typedef  int /*<<< orphan*/  sd_login_monitor ;

/* Variables and functions */
 int /*<<< orphan*/  CLOCK_MONOTONIC ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ now (int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  printf (char*) ; 
 int /*<<< orphan*/  sd_login_monitor_flush (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_login_monitor_get_events (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sd_login_monitor_get_fd (int /*<<< orphan*/ *) ; 
 scalar_t__ sd_login_monitor_get_timeout (int /*<<< orphan*/ *,scalar_t__*) ; 
 int sd_login_monitor_new (char*,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  sd_login_monitor_unref (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_monitor(void) {
        sd_login_monitor *m = NULL;
        unsigned n;
        int r;

        r = sd_login_monitor_new("session", &m);
        assert_se(r >= 0);

        for (n = 0; n < 5; n++) {
                struct pollfd pollfd = {};
                usec_t timeout, nw;

                assert_se((pollfd.fd = sd_login_monitor_get_fd(m)) >= 0);
                assert_se((pollfd.events = sd_login_monitor_get_events(m)) >= 0);

                assert_se(sd_login_monitor_get_timeout(m, &timeout) >= 0);

                nw = now(CLOCK_MONOTONIC);

                r = poll(&pollfd, 1,
                         timeout == (uint64_t) -1 ? -1 :
                         timeout > nw ? (int) ((timeout - nw) / 1000) :
                         0);

                assert_se(r >= 0);

                sd_login_monitor_flush(m);
                printf("Wake!\n");
        }

        sd_login_monitor_unref(m);
}