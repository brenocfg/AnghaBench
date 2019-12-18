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
typedef  int uint32_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET6 ; 
 int /*<<< orphan*/  AF_UNSPEC ; 
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  ERANGE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int /*<<< orphan*/  parse_mtu (int /*<<< orphan*/ ,char*,int*) ; 

__attribute__((used)) static void test_parse_mtu(void) {
        uint32_t mtu = 0;

        assert_se(parse_mtu(AF_UNSPEC, "1500", &mtu) >= 0 && mtu == 1500);
        assert_se(parse_mtu(AF_UNSPEC, "1400", &mtu) >= 0 && mtu == 1400);
        assert_se(parse_mtu(AF_UNSPEC, "65535", &mtu) >= 0 && mtu == 65535);
        assert_se(parse_mtu(AF_UNSPEC, "65536", &mtu) >= 0 && mtu == 65536);
        assert_se(parse_mtu(AF_UNSPEC, "4294967295", &mtu) >= 0 && mtu == 4294967295);
        assert_se(parse_mtu(AF_UNSPEC, "500", &mtu) >= 0 && mtu == 500);
        assert_se(parse_mtu(AF_UNSPEC, "1280", &mtu) >= 0 && mtu == 1280);
        assert_se(parse_mtu(AF_INET6, "1280", &mtu) >= 0 && mtu == 1280);
        assert_se(parse_mtu(AF_INET6, "1279", &mtu) == -ERANGE);
        assert_se(parse_mtu(AF_UNSPEC, "4294967296", &mtu) == -ERANGE);
        assert_se(parse_mtu(AF_INET6, "4294967296", &mtu) == -ERANGE);
        assert_se(parse_mtu(AF_INET6, "68", &mtu) == -ERANGE);
        assert_se(parse_mtu(AF_UNSPEC, "68", &mtu) >= 0 && mtu == 68);
        assert_se(parse_mtu(AF_UNSPEC, "67", &mtu) == -ERANGE);
        assert_se(parse_mtu(AF_UNSPEC, "0", &mtu) == -ERANGE);
        assert_se(parse_mtu(AF_UNSPEC, "", &mtu) == -EINVAL);
}