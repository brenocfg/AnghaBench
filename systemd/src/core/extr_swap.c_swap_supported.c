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
 int /*<<< orphan*/  F_OK ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 scalar_t__ detect_container () ; 

__attribute__((used)) static bool swap_supported(void) {
        static int supported = -1;

        /* If swap support is not available in the kernel, or we are
         * running in a container we don't support swap units, and any
         * attempts to starting one should fail immediately. */

        if (supported < 0)
                supported =
                        access("/proc/swaps", F_OK) >= 0 &&
                        detect_container() <= 0;

        return supported;
}