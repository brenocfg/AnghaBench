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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int DEVICE_MAJOR_VALID (unsigned int) ; 
 int DEVICE_MINOR_VALID (unsigned int) ; 
 unsigned int UINT32_MAX ; 
 unsigned int UINT64_MAX ; 
 int /*<<< orphan*/  assert_cc (int) ; 
 int /*<<< orphan*/  assert_se (int) ; 
 unsigned int major (int /*<<< orphan*/ ) ; 
 unsigned int minor (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_device_major_minor_valid(void) {
        /* on glibc dev_t is 64bit, even though in the kernel it is only 32bit */
        assert_cc(sizeof(dev_t) == sizeof(uint64_t));

        assert_se(DEVICE_MAJOR_VALID(0U));
        assert_se(DEVICE_MINOR_VALID(0U));

        assert_se(DEVICE_MAJOR_VALID(1U));
        assert_se(DEVICE_MINOR_VALID(1U));

        assert_se(!DEVICE_MAJOR_VALID(-1U));
        assert_se(!DEVICE_MINOR_VALID(-1U));

        assert_se(DEVICE_MAJOR_VALID(1U << 10));
        assert_se(DEVICE_MINOR_VALID(1U << 10));

        assert_se(DEVICE_MAJOR_VALID((1U << 12) - 1));
        assert_se(DEVICE_MINOR_VALID((1U << 20) - 1));

        assert_se(!DEVICE_MAJOR_VALID((1U << 12)));
        assert_se(!DEVICE_MINOR_VALID((1U << 20)));

        assert_se(!DEVICE_MAJOR_VALID(1U << 25));
        assert_se(!DEVICE_MINOR_VALID(1U << 25));

        assert_se(!DEVICE_MAJOR_VALID(UINT32_MAX));
        assert_se(!DEVICE_MINOR_VALID(UINT32_MAX));

        assert_se(!DEVICE_MAJOR_VALID(UINT64_MAX));
        assert_se(!DEVICE_MINOR_VALID(UINT64_MAX));

        assert_se(DEVICE_MAJOR_VALID(major(0)));
        assert_se(DEVICE_MINOR_VALID(minor(0)));
}