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
typedef  unsigned long uint64_t ;
typedef  scalar_t__ cap_value_t ;
typedef  int /*<<< orphan*/  cap_t ;

/* Variables and functions */
 int /*<<< orphan*/  CAP_INHERITABLE ; 
 int /*<<< orphan*/  CAP_SET ; 
 unsigned long UINT64_C (int) ; 
 unsigned long cap_last_cap () ; 
 scalar_t__ cap_set_flag (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,scalar_t__*,int /*<<< orphan*/ ) ; 
 int errno ; 

int capability_update_inherited_set(cap_t caps, uint64_t set) {
        unsigned long i;

        /* Add capabilities in the set to the inherited caps. Do not apply
         * them yet. */

        for (i = 0; i <= cap_last_cap(); i++) {

                if (set & (UINT64_C(1) << i)) {
                        cap_value_t v;

                        v = (cap_value_t) i;

                        /* Make the capability inheritable. */
                        if (cap_set_flag(caps, CAP_INHERITABLE, 1, &v, CAP_SET) < 0)
                                return -errno;
                }
        }

        return 0;
}