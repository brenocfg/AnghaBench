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
typedef  int /*<<< orphan*/  Condition ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_DIRECTORY_NOT_EMPTY ; 
 int /*<<< orphan*/  CONDITION_FILE_IS_EXECUTABLE ; 
 int /*<<< orphan*/  CONDITION_FILE_NOT_EMPTY ; 
 int /*<<< orphan*/  CONDITION_PATH_EXISTS ; 
 int /*<<< orphan*/  CONDITION_PATH_EXISTS_GLOB ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_DIRECTORY ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_MOUNT_POINT ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_READ_WRITE ; 
 int /*<<< orphan*/  CONDITION_PATH_IS_SYMBOLIC_LINK ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  condition_free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * condition_new (int /*<<< orphan*/ ,char*,int,int) ; 
 scalar_t__ condition_test (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_condition_test_path(void) {
        Condition *condition;

        condition = condition_new(CONDITION_PATH_EXISTS, "/bin/sh", false, false);
        assert_se(condition);
        assert_se(condition_test(condition));
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_EXISTS, "/bin/s?", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_EXISTS_GLOB, "/bin/s?", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_EXISTS_GLOB, "/bin/s?", false, true);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_EXISTS, "/thiscertainlywontexist", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_EXISTS, "/thiscertainlywontexist", false, true);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_IS_DIRECTORY, "/bin", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_DIRECTORY_NOT_EMPTY, "/bin", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_FILE_NOT_EMPTY, "/bin/sh", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_FILE_IS_EXECUTABLE, "/bin/sh", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_FILE_IS_EXECUTABLE, "/etc/passwd", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_IS_MOUNT_POINT, "/proc", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_IS_MOUNT_POINT, "/", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_IS_MOUNT_POINT, "/bin", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) == 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_IS_READ_WRITE, "/tmp", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);

        condition = condition_new(CONDITION_PATH_IS_SYMBOLIC_LINK, "/dev/stdout", false, false);
        assert_se(condition);
        assert_se(condition_test(condition) > 0);
        condition_free(condition);
}