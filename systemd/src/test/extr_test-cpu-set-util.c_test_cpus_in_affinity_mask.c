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
 int /*<<< orphan*/  assert (int) ; 
 int cpus_in_affinity_mask () ; 
 int /*<<< orphan*/  log_info (char*,int) ; 

__attribute__((used)) static void test_cpus_in_affinity_mask(void) {
        int r;

        r = cpus_in_affinity_mask();
        assert(r > 0);
        log_info("cpus_in_affinity_mask: %d", r);
}