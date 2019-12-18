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
 int /*<<< orphan*/  CPU_ALLOC_SIZE (int) ; 
 int /*<<< orphan*/  log_info (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_cpu_set_to_from_dbus () ; 
 int /*<<< orphan*/  test_cpus_in_affinity_mask () ; 
 int /*<<< orphan*/  test_parse_cpu_set () ; 
 int /*<<< orphan*/  test_parse_cpu_set_extend () ; 

int main(int argc, char *argv[]) {
        log_info("CPU_ALLOC_SIZE(1) = %zu", CPU_ALLOC_SIZE(1));
        log_info("CPU_ALLOC_SIZE(9) = %zu", CPU_ALLOC_SIZE(9));
        log_info("CPU_ALLOC_SIZE(64) = %zu", CPU_ALLOC_SIZE(64));
        log_info("CPU_ALLOC_SIZE(65) = %zu", CPU_ALLOC_SIZE(65));
        log_info("CPU_ALLOC_SIZE(1024) = %zu", CPU_ALLOC_SIZE(1024));
        log_info("CPU_ALLOC_SIZE(1025) = %zu", CPU_ALLOC_SIZE(1025));
        log_info("CPU_ALLOC_SIZE(8191) = %zu", CPU_ALLOC_SIZE(8191));

        test_parse_cpu_set();
        test_parse_cpu_set_extend();
        test_cpus_in_affinity_mask();
        test_cpu_set_to_from_dbus();

        return 0;
}