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
 int O_CLOEXEC ; 
 int O_DIRECTORY ; 
 int O_NOFOLLOW ; 
 int O_RDONLY ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int fd_is_cgroup_fs (int) ; 
 scalar_t__ fd_is_temporary_fs (int) ; 
 int open (char*,int) ; 
 int safe_close (int) ; 

__attribute__((used)) static void test_fd_is_cgroup_fs(void) {
        int fd;

        fd = open("/sys/fs/cgroup", O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);
        assert_se(fd >= 0);
        if (fd_is_temporary_fs(fd)) {
                fd = safe_close(fd);
                fd = open("/sys/fs/cgroup/systemd", O_RDONLY|O_DIRECTORY|O_CLOEXEC|O_NOFOLLOW);
                assert_se(fd >= 0);
        }
        assert_se(fd_is_cgroup_fs(fd));
        fd = safe_close(fd);
}