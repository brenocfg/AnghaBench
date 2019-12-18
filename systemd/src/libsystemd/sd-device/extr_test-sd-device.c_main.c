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
 int /*<<< orphan*/  LOG_INFO ; 
 int /*<<< orphan*/  test_sd_device_enumerator_devices () ; 
 int /*<<< orphan*/  test_sd_device_enumerator_filter_subsystem () ; 
 int /*<<< orphan*/  test_sd_device_enumerator_subsystems () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char **argv) {
        test_setup_logging(LOG_INFO);

        test_sd_device_enumerator_devices();
        test_sd_device_enumerator_subsystems();
        test_sd_device_enumerator_filter_subsystem();

        return 0;
}