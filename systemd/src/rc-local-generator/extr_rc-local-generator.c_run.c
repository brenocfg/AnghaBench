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
 int /*<<< orphan*/  RC_LOCAL_SCRIPT_PATH_START ; 
 int add_symlink (char*,char*) ; 
 char const* arg_dest ; 
 int /*<<< orphan*/  assert_se (char const*) ; 
 scalar_t__ check_executable (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_debug (char*) ; 

__attribute__((used)) static int run(const char *dest, const char *dest_early, const char *dest_late) {
        int r = 0, k = 0;

        assert_se(arg_dest = dest);

        if (check_executable(RC_LOCAL_SCRIPT_PATH_START) >= 0) {
                log_debug("Automatically adding rc-local.service.");

                r = add_symlink("rc-local.service", "multi-user.target");
        }

        return r < 0 ? r : k;
}