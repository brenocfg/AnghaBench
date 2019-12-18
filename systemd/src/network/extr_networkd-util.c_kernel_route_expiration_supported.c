#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* parameter; int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ Condition ;

/* Variables and functions */
 int /*<<< orphan*/  CONDITION_KERNEL_VERSION ; 
 int condition_test (TYPE_1__*) ; 

int kernel_route_expiration_supported(void) {
        static int cached = -1;
        int r;

        if (cached < 0) {
                Condition c = {
                        .type = CONDITION_KERNEL_VERSION,
                        .parameter = (char *) ">= 4.5"
                };
                r = condition_test(&c);
                if (r < 0)
                        return r;

                cached = r;
        }
        return cached;
}