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
 int /*<<< orphan*/  SYSTEMD_CGROUP_CONTROLLER ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ cg_attach (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cg_create (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cg_create_and_attach (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cg_get_path (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,char**) ; 
 scalar_t__ cg_is_empty (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cg_is_empty_recursive (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cg_kill_recursive (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ cg_migrate_recursive (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ cg_pid_get_path (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char**) ; 
 scalar_t__ cg_rmdir (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ cg_split_spec (char*,char**,char**) ; 
 int /*<<< orphan*/  cg_trim (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  getpid_cached () ; 
 int path_equal (char*,char*) ; 
 int streq (char*,char*) ; 

int main(int argc, char *argv[]) {
        char *path;
        char *c, *p;

        assert_se(cg_create(SYSTEMD_CGROUP_CONTROLLER, "/test-a") == 0);
        assert_se(cg_create(SYSTEMD_CGROUP_CONTROLLER, "/test-a") == 0);
        assert_se(cg_create(SYSTEMD_CGROUP_CONTROLLER, "/test-b") == 0);
        assert_se(cg_create(SYSTEMD_CGROUP_CONTROLLER, "/test-b/test-c") == 0);
        assert_se(cg_create_and_attach(SYSTEMD_CGROUP_CONTROLLER, "/test-b", 0) == 0);

        assert_se(cg_pid_get_path(SYSTEMD_CGROUP_CONTROLLER, getpid_cached(), &path) == 0);
        assert_se(streq(path, "/test-b"));
        free(path);

        assert_se(cg_attach(SYSTEMD_CGROUP_CONTROLLER, "/test-a", 0) == 0);

        assert_se(cg_pid_get_path(SYSTEMD_CGROUP_CONTROLLER, getpid_cached(), &path) == 0);
        assert_se(path_equal(path, "/test-a"));
        free(path);

        assert_se(cg_create_and_attach(SYSTEMD_CGROUP_CONTROLLER, "/test-b/test-d", 0) == 0);

        assert_se(cg_pid_get_path(SYSTEMD_CGROUP_CONTROLLER, getpid_cached(), &path) == 0);
        assert_se(path_equal(path, "/test-b/test-d"));
        free(path);

        assert_se(cg_get_path(SYSTEMD_CGROUP_CONTROLLER, "/test-b/test-d", NULL, &path) == 0);
        assert_se(path_equal(path, "/sys/fs/cgroup/systemd/test-b/test-d"));
        free(path);

        assert_se(cg_is_empty(SYSTEMD_CGROUP_CONTROLLER, "/test-a") > 0);
        assert_se(cg_is_empty(SYSTEMD_CGROUP_CONTROLLER, "/test-b") > 0);
        assert_se(cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-a") > 0);
        assert_se(cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-b") == 0);

        assert_se(cg_kill_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-a", 0, 0, NULL, NULL, NULL) == 0);
        assert_se(cg_kill_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-b", 0, 0, NULL, NULL, NULL) > 0);

        assert_se(cg_migrate_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-b", SYSTEMD_CGROUP_CONTROLLER, "/test-a", 0) > 0);

        assert_se(cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-a") == 0);
        assert_se(cg_is_empty_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-b") > 0);

        assert_se(cg_kill_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-a", 0, 0, NULL, NULL, NULL) > 0);
        assert_se(cg_kill_recursive(SYSTEMD_CGROUP_CONTROLLER, "/test-b", 0, 0, NULL, NULL, NULL) == 0);

        cg_trim(SYSTEMD_CGROUP_CONTROLLER, "/", false);

        assert_se(cg_rmdir(SYSTEMD_CGROUP_CONTROLLER, "/test-b") < 0);
        assert_se(cg_rmdir(SYSTEMD_CGROUP_CONTROLLER, "/test-a") >= 0);

        assert_se(cg_split_spec("foobar:/", &c, &p) == 0);
        assert_se(streq(c, "foobar"));
        assert_se(streq(p, "/"));
        free(c);
        free(p);

        assert_se(cg_split_spec("foobar:", &c, &p) < 0);
        assert_se(cg_split_spec("foobar:asdfd", &c, &p) < 0);
        assert_se(cg_split_spec(":///", &c, &p) < 0);
        assert_se(cg_split_spec(":", &c, &p) < 0);
        assert_se(cg_split_spec("", &c, &p) < 0);
        assert_se(cg_split_spec("fo/obar:/", &c, &p) < 0);

        assert_se(cg_split_spec("/", &c, &p) >= 0);
        assert_se(c == NULL);
        assert_se(streq(p, "/"));
        free(p);

        assert_se(cg_split_spec("foo", &c, &p) >= 0);
        assert_se(streq(c, "foo"));
        assert_se(p == NULL);
        free(c);

        return 0;
}