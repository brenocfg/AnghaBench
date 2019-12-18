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
 int EXIT_FAILURE ; 
 int /*<<< orphan*/  LOG_DEBUG ; 
 int /*<<< orphan*/  log_error (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  program_invocation_short_name ; 
 int test_ll (char*,char*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        if (argc == 2)
                return test_ll(argv[1], NULL);
        else if (argc == 3)
                return test_ll(argv[1], argv[2]);
        else {
                log_error("This program takes one or two arguments.\n"
                          "\t %s <ifname> [<seed>]", program_invocation_short_name);
                return EXIT_FAILURE;
        }
}