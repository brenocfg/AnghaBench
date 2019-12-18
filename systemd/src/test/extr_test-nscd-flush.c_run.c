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
 int /*<<< orphan*/  STRV_MAKE (char*,char*,char*) ; 
 int log_error_errno (int,char*) ; 
 int nscd_flush_cache (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int run(int argc, char *argv[]) {
        int r;

        test_setup_logging(LOG_DEBUG);

        r = nscd_flush_cache(STRV_MAKE("group", "passwd", "hosts"));
        if (r < 0)
                return log_error_errno(r, "Failed to flush NSCD cache");

        return 0;
}