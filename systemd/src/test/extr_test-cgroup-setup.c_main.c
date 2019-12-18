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
 int /*<<< orphan*/  test_is_wanted () ; 
 int /*<<< orphan*/  test_is_wanted_print (int) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(void) {
        test_setup_logging(LOG_DEBUG);

        test_is_wanted_print(true);
        test_is_wanted_print(false); /* run twice to test caching */
        test_is_wanted();

        return 0;
}