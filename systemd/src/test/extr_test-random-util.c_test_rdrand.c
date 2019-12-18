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
 int /*<<< orphan*/  log_error_errno (int,char*) ; 
 int /*<<< orphan*/  printf (char*,unsigned long) ; 
 int rdrand (unsigned long*) ; 

__attribute__((used)) static void test_rdrand(void) {
        int r, i;

        for (i = 0; i < 10; i++) {
                unsigned long x = 0;

                r = rdrand(&x);
                if (r < 0) {
                        log_error_errno(r, "RDRAND failed: %m");
                        return;
                }

                printf("%lx\n", x);
        }
}