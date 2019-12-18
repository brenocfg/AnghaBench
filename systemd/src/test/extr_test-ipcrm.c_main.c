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
typedef  int /*<<< orphan*/  uid_t ;

/* Variables and functions */
 int ESRCH ; 
 int EXIT_FAILURE ; 
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_INFO ; 
 char* NOBODY_USER_NAME ; 
 int clean_ipc_by_uid (int /*<<< orphan*/ ) ; 
 int get_user_creds (char const**,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  log_error_errno (int,char*,char const*) ; 
 int log_tests_skipped (char*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        uid_t uid;
        int r;
        const char* name = argv[1] ?: NOBODY_USER_NAME;

        test_setup_logging(LOG_INFO);

        r = get_user_creds(&name, &uid, NULL, NULL, NULL, 0);
        if (r == -ESRCH)
                return log_tests_skipped("Failed to resolve user");
        if (r < 0) {
                log_error_errno(r, "Failed to resolve \"%s\": %m", name);
                return EXIT_FAILURE;
        }

        r = clean_ipc_by_uid(uid);
        return  r < 0 ? EXIT_FAILURE : EXIT_SUCCESS;
}