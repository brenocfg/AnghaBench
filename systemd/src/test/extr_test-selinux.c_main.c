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
 int /*<<< orphan*/  LOG_DEBUG ; 
 char* SYSTEMD_BINARY_PATH ; 
 int /*<<< orphan*/  test_cleanup () ; 
 int /*<<< orphan*/  test_create_file_prepare (char const*) ; 
 int /*<<< orphan*/  test_loading () ; 
 int /*<<< orphan*/  test_misc (char const*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_testing () ; 

int main(int argc, char **argv) {
        const char *path = SYSTEMD_BINARY_PATH;
        if (argc >= 2)
                path = argv[1];

        test_setup_logging(LOG_DEBUG);

        test_testing();
        test_loading();
        test_misc(path);
        test_create_file_prepare(path);
        test_cleanup();

        return 0;
}