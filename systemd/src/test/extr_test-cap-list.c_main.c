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
 int /*<<< orphan*/  test_cap_list () ; 
 int /*<<< orphan*/  test_capability_set () ; 

int main(int argc, char *argv[]) {
        test_cap_list();
        test_capability_set();

        return 0;
}