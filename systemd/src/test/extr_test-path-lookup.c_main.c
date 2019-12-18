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
 int EXIT_SUCCESS ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  UNIT_FILE_GLOBAL ; 
 int /*<<< orphan*/  UNIT_FILE_SYSTEM ; 
 int /*<<< orphan*/  UNIT_FILE_USER ; 
 int /*<<< orphan*/  print_generator_binary_paths (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_paths (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_user_and_global_paths () ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_DEBUG);

        test_paths(UNIT_FILE_SYSTEM);
        test_paths(UNIT_FILE_USER);
        test_paths(UNIT_FILE_GLOBAL);

        test_user_and_global_paths();

        print_generator_binary_paths(UNIT_FILE_SYSTEM);
        print_generator_binary_paths(UNIT_FILE_USER);

        return EXIT_SUCCESS;
}