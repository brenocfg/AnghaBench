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
typedef  int /*<<< orphan*/  ExecCommandFlags ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  EXEC_COMMAND_AMBIENT_MAGIC ; 
 int /*<<< orphan*/  EXEC_COMMAND_FULLY_PRIVILEGED ; 
 int /*<<< orphan*/  EXEC_COMMAND_IGNORE_FAILURE ; 
 int /*<<< orphan*/  EXEC_COMMAND_NO_ENV_EXPAND ; 
 int /*<<< orphan*/  EXEC_COMMAND_NO_SETUID ; 
 int FLAGS_SET (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 char** STRV_MAKE (char*,char*,char*,...) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int exec_command_flags_from_strv (char**,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_exec_command_flags_from_strv(void) {
        ExecCommandFlags flags = 0;
        char **valid_strv = STRV_MAKE("no-env-expand", "no-setuid", "ignore-failure");
        char **invalid_strv = STRV_MAKE("no-env-expand", "no-setuid", "nonexistent-option", "ignore-failure");
        int r;

        r = exec_command_flags_from_strv(valid_strv, &flags);

        assert_se(r == 0);
        assert_se(FLAGS_SET(flags, EXEC_COMMAND_NO_ENV_EXPAND));
        assert_se(FLAGS_SET(flags, EXEC_COMMAND_NO_SETUID));
        assert_se(FLAGS_SET(flags, EXEC_COMMAND_IGNORE_FAILURE));
        assert_se(!FLAGS_SET(flags, EXEC_COMMAND_AMBIENT_MAGIC));
        assert_se(!FLAGS_SET(flags, EXEC_COMMAND_FULLY_PRIVILEGED));

        r = exec_command_flags_from_strv(invalid_strv, &flags);

        assert_se(r == -EINVAL);
}