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

/* Variables and functions */
 int ENOMEDIUM ; 
 int IN_SET (int,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int cg_all_unified () ; 
 int cg_hybrid_unified () ; 
 int cg_unified () ; 
 int cg_unified_controller (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_notice_errno (int,char*) ; 

__attribute__((used)) static void test_cg_tests(void) {
        int all, hybrid, systemd, r;

        r = cg_unified();
        if (r == -ENOMEDIUM) {
                log_notice_errno(r, "Skipping cg hierarchy tests: %m");
                return;
        }
        assert_se(r >= 0);

        all = cg_all_unified();
        assert_se(IN_SET(all, 0, 1));

        hybrid = cg_hybrid_unified();
        assert_se(IN_SET(hybrid, 0, 1));

        systemd = cg_unified_controller(SYSTEMD_CGROUP_CONTROLLER);
        assert_se(IN_SET(systemd, 0, 1));

        if (all) {
                assert_se(systemd);
                assert_se(!hybrid);

        } else if (hybrid) {
                assert_se(systemd);
                assert_se(!all);

        } else
                assert_se(!systemd);
}