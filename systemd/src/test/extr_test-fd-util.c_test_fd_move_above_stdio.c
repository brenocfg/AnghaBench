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
 scalar_t__ EBADF ; 
 int /*<<< orphan*/  F_DUPFD ; 
 int /*<<< orphan*/  O_RDONLY ; 
 int /*<<< orphan*/  assert_se (int) ; 
 scalar_t__ close_nointr (int) ; 
 scalar_t__ dup (int) ; 
 int fcntl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int fd_move_above_stdio (int) ; 
 int open (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_fd_move_above_stdio(void) {
        int original_stdin, new_fd;

        original_stdin = fcntl(0, F_DUPFD, 3);
        assert_se(original_stdin >= 3);
        assert_se(close_nointr(0) != EBADF);

        new_fd = open("/dev/null", O_RDONLY);
        assert_se(new_fd == 0);

        new_fd = fd_move_above_stdio(new_fd);
        assert_se(new_fd >= 3);

        assert_se(dup(original_stdin) == 0);
        assert_se(close_nointr(original_stdin) != EBADF);
        assert_se(close_nointr(new_fd) != EBADF);
}