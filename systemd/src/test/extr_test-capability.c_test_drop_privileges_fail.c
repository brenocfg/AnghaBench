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
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ drop_privileges (scalar_t__,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int /*<<< orphan*/  test_flags ; 
 scalar_t__ test_gid ; 
 scalar_t__ test_uid ; 

__attribute__((used)) static void test_drop_privileges_fail(void) {
        assert_se(drop_privileges(test_uid, test_gid, test_flags) >= 0);
        assert_se(getuid() == test_uid);
        assert_se(getgid() == test_gid);

        assert_se(drop_privileges(test_uid, test_gid, test_flags) < 0);
        assert_se(drop_privileges(0, 0, test_flags) < 0);
}