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
 int NSEC_PER_MSEC ; 
 int NSEC_PER_SEC ; 
 int /*<<< orphan*/  test_config_parse_nsec_one (char*,int) ; 

__attribute__((used)) static void test_config_parse_nsec(void) {
        test_config_parse_nsec_one("1", 1);
        test_config_parse_nsec_one("1s", 1 * NSEC_PER_SEC);
        test_config_parse_nsec_one("100ms", 100 * NSEC_PER_MSEC);
        test_config_parse_nsec_one("5min 20s", 5 * 60 * NSEC_PER_SEC + 20 * NSEC_PER_SEC);

        test_config_parse_nsec_one("-1", 0);
        test_config_parse_nsec_one("10foo", 0);
        test_config_parse_nsec_one("garbage", 0);
}