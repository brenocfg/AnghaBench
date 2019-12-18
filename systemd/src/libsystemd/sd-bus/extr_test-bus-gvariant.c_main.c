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
 int /*<<< orphan*/  test_bus_gvariant_get_alignment () ; 
 int /*<<< orphan*/  test_bus_gvariant_get_size () ; 
 int /*<<< orphan*/  test_bus_gvariant_is_fixed_size () ; 
 int test_marshal () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_DEBUG);

        test_bus_gvariant_is_fixed_size();
        test_bus_gvariant_get_size();
        test_bus_gvariant_get_alignment();

        return test_marshal();
}