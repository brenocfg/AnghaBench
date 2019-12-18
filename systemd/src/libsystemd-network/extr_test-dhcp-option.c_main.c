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
 unsigned int ELEMENTSOF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * option_tests ; 
 int /*<<< orphan*/  test_invalid_buffer_length () ; 
 int /*<<< orphan*/  test_message_init () ; 
 int /*<<< orphan*/  test_option_set () ; 
 int /*<<< orphan*/  test_options (int /*<<< orphan*/ *) ; 

int main(int argc, char *argv[]) {
        unsigned i;

        test_invalid_buffer_length();
        test_message_init();

        test_options(NULL);

        for (i = 0; i < ELEMENTSOF(option_tests); i++)
                test_options(&option_tests[i]);

        test_option_set();

        return 0;
}