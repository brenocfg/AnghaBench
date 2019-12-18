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
typedef  int uint64_t ;

/* Variables and functions */
 int EINVAL ; 
 int ERANGE ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int safe_atou64 (char*,int*) ; 

__attribute__((used)) static void test_safe_atou64(void) {
        int r;
        uint64_t l;

        r = safe_atou64("12345", &l);
        assert_se(r == 0);
        assert_se(l == 12345);

        r = safe_atou64("  12345", &l);
        assert_se(r == 0);
        assert_se(l == 12345);

        r = safe_atou64("18446744073709551617", &l);
        assert_se(r == -ERANGE);

        r = safe_atou64("-1", &l);
        assert_se(r == -ERANGE);

        r = safe_atou64("  -1", &l);
        assert_se(r == -ERANGE);

        r = safe_atou64("junk", &l);
        assert_se(r == -EINVAL);

        r = safe_atou64("123x", &l);
        assert_se(r == -EINVAL);

        r = safe_atou64("12.3", &l);
        assert_se(r == -EINVAL);

        r = safe_atou64("", &l);
        assert_se(r == -EINVAL);
}