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
struct statfs {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  assert_se (int) ; 
 int is_cgroup_fs (struct statfs*) ; 
 scalar_t__ is_temporary_fs (struct statfs*) ; 
 scalar_t__ statfs (char*,struct statfs*) ; 

__attribute__((used)) static void test_is_cgroup_fs(void) {
        struct statfs sfs;
        assert_se(statfs("/sys/fs/cgroup", &sfs) == 0);
        if (is_temporary_fs(&sfs))
                assert_se(statfs("/sys/fs/cgroup/systemd", &sfs) == 0);
        assert_se(is_cgroup_fs(&sfs));
}