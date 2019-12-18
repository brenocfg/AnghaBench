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
 int test_ref_unref () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        test_setup_logging(LOG_INFO);

        r = test_ref_unref();
        if (r < 0)
                return r;

        return 0;
}