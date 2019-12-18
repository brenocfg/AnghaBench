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
typedef  int /*<<< orphan*/  sd_bus_message ;
typedef  int /*<<< orphan*/  sd_bus_error ;

/* Variables and functions */
 size_t ELEMENTSOF (int*) ; 
 size_t PTR_TO_UINT (void*) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  log_info (char*,size_t) ; 
 int* mask ; 

__attribute__((used)) static int filter(sd_bus_message *m, void *userdata, sd_bus_error *ret_error) {
        log_info("Ran %u", PTR_TO_UINT(userdata));
        assert_se(PTR_TO_UINT(userdata) < ELEMENTSOF(mask));
        mask[PTR_TO_UINT(userdata)] = true;
        return 0;
}