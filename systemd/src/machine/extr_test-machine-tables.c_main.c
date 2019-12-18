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
 int /*<<< orphan*/  KILL_WHO ; 
 int /*<<< orphan*/  MACHINE_CLASS ; 
 int /*<<< orphan*/  MACHINE_STATE ; 
 int /*<<< orphan*/  kill_who ; 
 int /*<<< orphan*/  machine_class ; 
 int /*<<< orphan*/  machine_state ; 
 int /*<<< orphan*/  test_table (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
        test_table(kill_who, KILL_WHO);
        test_table(machine_class, MACHINE_CLASS);
        test_table(machine_state, MACHINE_STATE);

        return EXIT_SUCCESS;
}