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
 int /*<<< orphan*/  dump_mapping_table () ; 
 int /*<<< orphan*/  test_errno_mapping_custom () ; 
 int /*<<< orphan*/  test_errno_mapping_standard () ; 
 int /*<<< orphan*/  test_error () ; 

int main(int argc, char *argv[]) {
        dump_mapping_table();

        test_error();
        test_errno_mapping_standard();
        test_errno_mapping_custom();

        return 0;
}