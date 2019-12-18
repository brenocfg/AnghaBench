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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  check_stop_unlink (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ manager_load_startable_unit_or_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 scalar_t__ mkdir_p (char const*,int) ; 
 int /*<<< orphan*/  strjoina (char const*,char*) ; 
 scalar_t__ touch (int /*<<< orphan*/ ) ; 
 scalar_t__ unit_start (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_path_directorynotempty(Manager *m) {
        const char *test_path = "/tmp/test-path_directorynotempty/";
        Unit *unit = NULL;

        assert_se(m);

        assert_se(access(test_path, F_OK) < 0);

        assert_se(manager_load_startable_unit_or_warn(m, "path-directorynotempty.path", NULL, &unit) >= 0);
        assert_se(unit_start(unit) >= 0);

        /* MakeDirectory default to no */
        assert_se(access(test_path, F_OK) < 0);

        assert_se(mkdir_p(test_path, 0755) >= 0);
        assert_se(touch(strjoina(test_path, "test_file")) >= 0);

        check_stop_unlink(m, unit, test_path, NULL);
}