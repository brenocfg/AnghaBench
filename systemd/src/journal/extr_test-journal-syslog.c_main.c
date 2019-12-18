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
 int /*<<< orphan*/  test_syslog_parse_identifier (char*,char*,char*,char*,int) ; 
 int /*<<< orphan*/  test_syslog_parse_priority (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int main(void) {
        test_syslog_parse_identifier("pidu[111]: xxx", "pidu", "111", "xxx", 11);
        test_syslog_parse_identifier("pidu: xxx", "pidu", NULL, "xxx", 6);
        test_syslog_parse_identifier("pidu:  xxx", "pidu", NULL, " xxx", 6);
        test_syslog_parse_identifier("pidu xxx", NULL, NULL, "pidu xxx", 0);
        test_syslog_parse_identifier("   pidu xxx", NULL, NULL, "   pidu xxx", 0);
        test_syslog_parse_identifier("", NULL, NULL, "", 0);
        test_syslog_parse_identifier("  ", NULL, NULL, "  ", 0);
        test_syslog_parse_identifier(":", "", NULL, "", 1);
        test_syslog_parse_identifier(":  ", "", NULL, " ", 2);
        test_syslog_parse_identifier(" :", "", NULL, "", 2);
        test_syslog_parse_identifier("   pidu:", "pidu", NULL, "", 8);
        test_syslog_parse_identifier("pidu:", "pidu", NULL, "", 5);
        test_syslog_parse_identifier("pidu: ", "pidu", NULL, "", 6);
        test_syslog_parse_identifier("pidu : ", NULL, NULL, "pidu : ", 0);

        test_syslog_parse_priority("<>", 0, 0);
        test_syslog_parse_priority("<>aaa", 0, 0);
        test_syslog_parse_priority("<aaaa>", 0, 0);
        test_syslog_parse_priority("<aaaa>aaa", 0, 0);
        test_syslog_parse_priority(" <aaaa>", 0, 0);
        test_syslog_parse_priority(" <aaaa>aaa", 0, 0);
        /* TODO: add test cases of valid priorities */

        return 0;
}