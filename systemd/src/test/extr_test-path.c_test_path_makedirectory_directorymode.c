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
struct stat {int st_mode; } ;
typedef  int /*<<< orphan*/  Unit ;
typedef  int /*<<< orphan*/  Manager ;

/* Variables and functions */
 int /*<<< orphan*/  F_OK ; 
 int REMOVE_PHYSICAL ; 
 int REMOVE_ROOT ; 
 int S_IRWXG ; 
 int S_IRWXO ; 
 int S_IRWXU ; 
 scalar_t__ access (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ manager_load_startable_unit_or_warn (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  rm_rf (char const*,int) ; 
 scalar_t__ stat (char const*,struct stat*) ; 
 scalar_t__ unit_start (int /*<<< orphan*/ *) ; 
 scalar_t__ unit_stop (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_path_makedirectory_directorymode(Manager *m) {
        const char *test_path = "/tmp/test-path_makedirectory/";
        Unit *unit = NULL;
        struct stat s;

        assert_se(m);

        assert_se(access(test_path, F_OK) < 0);

        assert_se(manager_load_startable_unit_or_warn(m, "path-makedirectory.path", NULL, &unit) >= 0);
        assert_se(unit_start(unit) >= 0);

        /* Check if the directory has been created */
        assert_se(access(test_path, F_OK) >= 0);

        /* Check the mode we specified with DirectoryMode=0744 */
        assert_se(stat(test_path, &s) >= 0);
        assert_se((s.st_mode & S_IRWXU) == 0700);
        assert_se((s.st_mode & S_IRWXG) == 0040);
        assert_se((s.st_mode & S_IRWXO) == 0004);

        assert_se(unit_stop(unit) >= 0);
        (void) rm_rf(test_path, REMOVE_ROOT|REMOVE_PHYSICAL);
}