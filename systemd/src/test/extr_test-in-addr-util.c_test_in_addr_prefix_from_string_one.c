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
typedef  union in_addr_union {int dummy; } in_addr_union ;

/* Variables and functions */
 int /*<<< orphan*/  PREFIXLEN_LEGACY ; 
 int /*<<< orphan*/  PREFIXLEN_REFUSE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int in_addr_equal (int,union in_addr_union*,union in_addr_union const*) ; 
 int in_addr_prefix_from_string (char const*,int,union in_addr_union*,unsigned char*) ; 
 int in_addr_prefix_from_string_auto (char const*,int*,union in_addr_union*,unsigned char*) ; 
 int in_addr_prefix_from_string_auto_internal (char const*,int /*<<< orphan*/ ,int*,union in_addr_union*,unsigned char*) ; 

__attribute__((used)) static void test_in_addr_prefix_from_string_one(
                const char *p,
                int family,
                int ret,
                const union in_addr_union *u,
                unsigned char prefixlen,
                int ret_refuse,
                unsigned char prefixlen_refuse,
                int ret_legacy,
                unsigned char prefixlen_legacy) {

        union in_addr_union q;
        unsigned char l;
        int f, r;

        r = in_addr_prefix_from_string(p, family, &q, &l);
        assert_se(r == ret);

        if (r < 0)
                return;

        assert_se(in_addr_equal(family, &q, u));
        assert_se(l == prefixlen);

        r = in_addr_prefix_from_string_auto(p, &f, &q, &l);
        assert_se(r >= 0);

        assert_se(f == family);
        assert_se(in_addr_equal(family, &q, u));
        assert_se(l == prefixlen);

        r = in_addr_prefix_from_string_auto_internal(p, PREFIXLEN_REFUSE, &f, &q, &l);
        assert_se(r == ret_refuse);

        if (r >= 0) {
                assert_se(f == family);
                assert_se(in_addr_equal(family, &q, u));
                assert_se(l == prefixlen_refuse);
        }

        r = in_addr_prefix_from_string_auto_internal(p, PREFIXLEN_LEGACY, &f, &q, &l);
        assert_se(r == ret_legacy);

        if (r >= 0) {
                assert_se(f == family);
                assert_se(in_addr_equal(family, &q, u));
                assert_se(l == prefixlen_legacy);
        }
}