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
 int /*<<< orphan*/  test_sd_event_code_migration () ; 
 int /*<<< orphan*/  test_strpcpy () ; 
 int /*<<< orphan*/  test_strpcpyf () ; 
 int /*<<< orphan*/  test_strpcpyl () ; 
 int /*<<< orphan*/  test_strscpy () ; 
 int /*<<< orphan*/  test_strscpyl () ; 

int main(int argc, char *argv[]) {
        test_strpcpy();
        test_strpcpyf();
        test_strpcpyl();
        test_strscpy();
        test_strscpyl();

        test_sd_event_code_migration();

        return 0;
}