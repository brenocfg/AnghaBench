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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int bar ; 
 int baz ; 
 int foo ; 
 int memory ; 
 int /*<<< orphan*/  static_destruct () ; 
 int strdup (char*) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_INFO);

        assert_se(memory = strdup("hallo"));

        assert_se(foo == 0 && bar == 0 && baz == 0);
        static_destruct();
        assert_se(foo == 1 && bar == 2 && baz == 3);

        return EXIT_SUCCESS;
}