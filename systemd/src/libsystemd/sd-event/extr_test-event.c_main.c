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
 int /*<<< orphan*/  test_basic () ; 
 int /*<<< orphan*/  test_inotify (int) ; 
 int /*<<< orphan*/  test_rtqueue () ; 
 int /*<<< orphan*/  test_sd_event_now () ; 
 int /*<<< orphan*/  test_setup_logging (int /*<<< orphan*/ ) ; 

int main(int argc, char *argv[]) {
        test_setup_logging(LOG_INFO);

        test_basic();
        test_sd_event_now();
        test_rtqueue();

        test_inotify(100); /* should work without overflow */
        test_inotify(33000); /* should trigger a q overflow */

        return 0;
}