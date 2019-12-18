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
typedef  int /*<<< orphan*/  dev_t ;

/* Variables and functions */
 int /*<<< orphan*/  EINVAL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int major (int /*<<< orphan*/ ) ; 
 int minor (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  parse_dev (char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void test_parse_dev(void) {
        dev_t dev;

        assert_se(parse_dev("", &dev) == -EINVAL);
        assert_se(parse_dev("junk", &dev) == -EINVAL);
        assert_se(parse_dev("0", &dev) == -EINVAL);
        assert_se(parse_dev("5", &dev) == -EINVAL);
        assert_se(parse_dev("5:", &dev) == -EINVAL);
        assert_se(parse_dev(":5", &dev) == -EINVAL);
        assert_se(parse_dev("-1:-1", &dev) == -EINVAL);
#if SIZEOF_DEV_T < 8
        assert_se(parse_dev("4294967295:4294967295", &dev) == -EINVAL);
#endif
        assert_se(parse_dev("8:11", &dev) >= 0 && major(dev) == 8 && minor(dev) == 11);
        assert_se(parse_dev("0:0", &dev) >= 0 && major(dev) == 0 && minor(dev) == 0);
}