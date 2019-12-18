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
 int /*<<< orphan*/  assert_se (int) ; 
 int unbase64char (char) ; 

__attribute__((used)) static void test_unbase64char(void) {
        assert_se(unbase64char('A') == 0);
        assert_se(unbase64char('Z') == 25);
        assert_se(unbase64char('a') == 26);
        assert_se(unbase64char('z') == 51);
        assert_se(unbase64char('0') == 52);
        assert_se(unbase64char('9') == 61);
        assert_se(unbase64char('+') == 62);
        assert_se(unbase64char('/') == 63);
        assert_se(unbase64char('=') == -EINVAL);
}