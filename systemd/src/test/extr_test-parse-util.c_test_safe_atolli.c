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
 int ERANGE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int safe_atolli (char*,long long*) ; 

__attribute__((used)) static void test_safe_atolli(void) {
        int r;
        long long l;

        r = safe_atolli("12345", &l);
        assert_se(r == 0);
        assert_se(l == 12345);

        r = safe_atolli("  12345", &l);
        assert_se(r == 0);
        assert_se(l == 12345);

        r = safe_atolli("-12345", &l);
        assert_se(r == 0);
        assert_se(l == -12345);

        r = safe_atolli("  -12345", &l);
        assert_se(r == 0);
        assert_se(l == -12345);

        r = safe_atolli("12345678901234567890", &l);
        assert_se(r == -ERANGE);

        r = safe_atolli("-12345678901234567890", &l);
        assert_se(r == -ERANGE);

        r = safe_atolli("junk", &l);
        assert_se(r == -EINVAL);

        r = safe_atolli("123x", &l);
        assert_se(r == -EINVAL);

        r = safe_atolli("12.3", &l);
        assert_se(r == -EINVAL);

        r = safe_atolli("", &l);
        assert_se(r == -EINVAL);
}