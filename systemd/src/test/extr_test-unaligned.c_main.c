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
 int /*<<< orphan*/  test_be () ; 
 int /*<<< orphan*/  test_le () ; 
 int /*<<< orphan*/  test_ne () ; 

int main(int argc, const char *argv[]) {
        test_be();
        test_le();
        test_ne();
        return 0;
}