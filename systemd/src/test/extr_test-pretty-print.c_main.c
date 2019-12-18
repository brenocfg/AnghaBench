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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  print_separator () ; 
 int /*<<< orphan*/  test_cat_files () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_terminal_urlify () ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_INFO);

        test_terminal_urlify();
        test_cat_files();

        print_separator();

        return 0;
}