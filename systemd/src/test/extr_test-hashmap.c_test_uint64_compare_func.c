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
 int /*<<< orphan*/  assert_se (int) ; 
 int uint64_compare_func (int const*,int const*) ; 

__attribute__((used)) static void test_uint64_compare_func(void) {
        const uint64_t a = 0x100, b = 0x101;

        assert_se(uint64_compare_func(&a, &a) == 0);
        assert_se(uint64_compare_func(&a, &b) == -1);
        assert_se(uint64_compare_func(&b, &a) == 1);
}