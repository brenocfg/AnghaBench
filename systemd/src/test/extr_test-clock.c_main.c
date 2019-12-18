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
 int /*<<< orphan*/  test_clock_is_localtime () ; 
 int /*<<< orphan*/  test_clock_is_localtime_system () ; 

int main(int argc, char *argv[]) {
        test_clock_is_localtime();
        test_clock_is_localtime_system();

        return 0;
}