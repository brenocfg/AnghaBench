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
 unsigned long long CAP_CHOWN ; 
 unsigned long long CAP_KILL ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ drop_privileges (scalar_t__,scalar_t__,unsigned long long) ; 
 scalar_t__ getgid () ; 
 scalar_t__ getuid () ; 
 int have_effective_cap (unsigned long long) ; 
 unsigned long long test_flags ; 
 scalar_t__ test_gid ; 
 scalar_t__ test_uid ; 

__attribute__((used)) static void test_have_effective_cap(void) {
        assert_se(have_effective_cap(CAP_KILL));
        assert_se(have_effective_cap(CAP_CHOWN));

        assert_se(drop_privileges(test_uid, test_gid, test_flags | (1ULL << CAP_KILL)) >= 0);
        assert_se(getuid() == test_uid);
        assert_se(getgid() == test_gid);

        assert_se(have_effective_cap(CAP_KILL));
        assert_se(!have_effective_cap(CAP_CHOWN));
}