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
 int EINVAL ; 
 int /*<<< orphan*/  IPPROTO_DCCP ; 
 int IPPROTO_IP ; 
 int IPPROTO_SCTP ; 
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  test_int (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_int_fail (int) ; 
 int /*<<< orphan*/  test_parse_ip_protocol (char*,int) ; 
 int /*<<< orphan*/  test_str (char*) ; 
 int /*<<< orphan*/  test_str_fail (char*) ; 

int main(int argc, const char *argv[]) {
        test_int(IPPROTO_TCP);
        test_int(IPPROTO_DCCP);
        test_int_fail(-1);
        test_int_fail(1024 * 1024);

        test_str("sctp");
        test_str("udp");
        test_str_fail("hoge");
        test_str_fail("-1");
        test_str_fail("1000000000");

        test_parse_ip_protocol("sctp", IPPROTO_SCTP);
        test_parse_ip_protocol("ScTp", IPPROTO_SCTP);
        test_parse_ip_protocol("ip", IPPROTO_IP);
        test_parse_ip_protocol("", IPPROTO_IP);
        test_parse_ip_protocol("1", 1);
        test_parse_ip_protocol("0", 0);
        test_parse_ip_protocol("-10", -EINVAL);
        test_parse_ip_protocol("100000000", -EINVAL);

        return 0;
}