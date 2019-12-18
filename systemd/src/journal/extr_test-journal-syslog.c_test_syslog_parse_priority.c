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
 int /*<<< orphan*/  assert_se (int) ; 
 int syslog_parse_priority (char const**,int*,int) ; 

__attribute__((used)) static void test_syslog_parse_priority(const char *str, int priority, int ret) {
        const char *buf = str;
        int priority2 = 0, ret2;

        ret2 = syslog_parse_priority(&buf, &priority2, false);

        assert_se(ret == ret2);
        if (ret2 == 1)
                assert_se(priority == priority2);
}