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
 int /*<<< orphan*/  test_dns_name_between_one (char*,char*,char*,int) ; 

__attribute__((used)) static void test_dns_name_between(void) {
        /* see https://tools.ietf.org/html/rfc4034#section-6.1
           Note that we use "\033.z.example" in stead of "\001.z.example" as we
           consider the latter invalid */
        test_dns_name_between_one("example", "a.example", "yljkjljk.a.example", true);
        test_dns_name_between_one("a.example", "yljkjljk.a.example", "Z.a.example", true);
        test_dns_name_between_one("yljkjljk.a.example", "Z.a.example", "zABC.a.EXAMPLE", true);
        test_dns_name_between_one("Z.a.example", "zABC.a.EXAMPLE", "z.example", true);
        test_dns_name_between_one("zABC.a.EXAMPLE", "z.example", "\\033.z.example", true);
        test_dns_name_between_one("z.example", "\\033.z.example", "*.z.example", true);
        test_dns_name_between_one("\\033.z.example", "*.z.example", "\\200.z.example", true);
        test_dns_name_between_one("*.z.example", "\\200.z.example", "example", true);
        test_dns_name_between_one("\\200.z.example", "example", "a.example", true);

        test_dns_name_between_one("example", "a.example", "example", true);
        test_dns_name_between_one("example", "example", "example", false);
        test_dns_name_between_one("example", "example", "yljkjljk.a.example", false);
        test_dns_name_between_one("example", "yljkjljk.a.example", "yljkjljk.a.example", false);
        test_dns_name_between_one("hkps.pool.sks-keyservers.net", "_pgpkey-https._tcp.hkps.pool.sks-keyservers.net", "ipv4.pool.sks-keyservers.net", true);
}