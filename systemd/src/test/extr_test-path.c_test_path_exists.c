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
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  check_stop_unlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ manager_load_startable_unit_or_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ touch (char const*) ; 
 scalar_t__ unit_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_path_exists(Manager *m) {
        const char *test_path = "/tmp/test-path_exists";
        Unit *unit = NULL;

        assert_se(m);

        assert_se(manager_load_startable_unit_or_warn(m, "path-exists.path", NULL, &unit) >= 0);
        assert_se(unit_start(unit) >= 0);

        assert_se(touch(test_path) >= 0);

        check_stop_unlink(m, unit, test_path, NULL);
}