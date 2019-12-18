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
 int IN_SET (int,int /*<<< orphan*/ ,int) ; 
 scalar_t__ access (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int clock_is_localtime (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  log_info (char*,int) ; 

__attribute__((used)) static void test_clock_is_localtime_system(void) {
        int r;
        r = clock_is_localtime(NULL);

        if (access("/etc/adjtime", F_OK) == 0) {
                log_info("/etc/adjtime exists, clock_is_localtime() == %i", r);
                /* if /etc/adjtime exists we expect some answer, no error or
                 * crash */
                assert_se(IN_SET(r, 0, 1));
        } else
                /* default is UTC if there is no /etc/adjtime */
                assert_se(r == 0);
}