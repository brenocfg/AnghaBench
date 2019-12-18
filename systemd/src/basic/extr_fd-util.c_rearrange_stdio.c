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
 int /*<<< orphan*/  F_DUPFD_CLOEXEC ; 
 int O_CLOEXEC ; 
 int O_RDONLY ; 
 int O_RDWR ; 
 int O_WRONLY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ dup2 (int,int) ; 
 int errno ; 
 int fcntl (int,int /*<<< orphan*/ ,int) ; 
 int fd_cloexec (int,int) ; 
 int open (char*,int) ; 
 int /*<<< orphan*/  safe_close (int) ; 
 int /*<<< orphan*/  safe_close_above_stdio (int) ; 

int rearrange_stdio(int original_input_fd, int original_output_fd, int original_error_fd) {

        int fd[3] = { /* Put together an array of fds we work on */
                original_input_fd,
                original_output_fd,
                original_error_fd
        };

        int r, i,
                null_fd = -1,                /* if we open /dev/null, we store the fd to it here */
                copy_fd[3] = { -1, -1, -1 }; /* This contains all fds we duplicate here temporarily, and hence need to close at the end */
        bool null_readable, null_writable;

        /* Sets up stdin, stdout, stderr with the three file descriptors passed in. If any of the descriptors is
         * specified as -1 it will be connected with /dev/null instead. If any of the file descriptors is passed as
         * itself (e.g. stdin as STDIN_FILENO) it is left unmodified, but the O_CLOEXEC bit is turned off should it be
         * on.
         *
         * Note that if any of the passed file descriptors are > 2 they will be closed — both on success and on
         * failure! Thus, callers should assume that when this function returns the input fds are invalidated.
         *
         * Note that when this function fails stdin/stdout/stderr might remain half set up!
         *
         * O_CLOEXEC is turned off for all three file descriptors (which is how it should be for
         * stdin/stdout/stderr). */

        null_readable = original_input_fd < 0;
        null_writable = original_output_fd < 0 || original_error_fd < 0;

        /* First step, open /dev/null once, if we need it */
        if (null_readable || null_writable) {

                /* Let's open this with O_CLOEXEC first, and convert it to non-O_CLOEXEC when we move the fd to the final position. */
                null_fd = open("/dev/null", (null_readable && null_writable ? O_RDWR :
                                             null_readable ? O_RDONLY : O_WRONLY) | O_CLOEXEC);
                if (null_fd < 0) {
                        r = -errno;
                        goto finish;
                }

                /* If this fd is in the 0…2 range, let's move it out of it */
                if (null_fd < 3) {
                        int copy;

                        copy = fcntl(null_fd, F_DUPFD_CLOEXEC, 3); /* Duplicate this with O_CLOEXEC set */
                        if (copy < 0) {
                                r = -errno;
                                goto finish;
                        }

                        safe_close(null_fd);
                        null_fd = copy;
                }
        }

        /* Let's assemble fd[] with the fds to install in place of stdin/stdout/stderr */
        for (i = 0; i < 3; i++) {

                if (fd[i] < 0)
                        fd[i] = null_fd;        /* A negative parameter means: connect this one to /dev/null */
                else if (fd[i] != i && fd[i] < 3) {
                        /* This fd is in the 0…2 territory, but not at its intended place, move it out of there, so that we can work there. */
                        copy_fd[i] = fcntl(fd[i], F_DUPFD_CLOEXEC, 3); /* Duplicate this with O_CLOEXEC set */
                        if (copy_fd[i] < 0) {
                                r = -errno;
                                goto finish;
                        }

                        fd[i] = copy_fd[i];
                }
        }

        /* At this point we now have the fds to use in fd[], and they are all above the stdio range, so that we
         * have freedom to move them around. If the fds already were at the right places then the specific fds are
         * -1. Let's now move them to the right places. This is the point of no return. */
        for (i = 0; i < 3; i++) {

                if (fd[i] == i) {

                        /* fd is already in place, but let's make sure O_CLOEXEC is off */
                        r = fd_cloexec(i, false);
                        if (r < 0)
                                goto finish;

                } else {
                        assert(fd[i] > 2);

                        if (dup2(fd[i], i) < 0) { /* Turns off O_CLOEXEC on the new fd. */
                                r = -errno;
                                goto finish;
                        }
                }
        }

        r = 0;

finish:
        /* Close the original fds, but only if they were outside of the stdio range. Also, properly check for the same
         * fd passed in multiple times. */
        safe_close_above_stdio(original_input_fd);
        if (original_output_fd != original_input_fd)
                safe_close_above_stdio(original_output_fd);
        if (original_error_fd != original_input_fd && original_error_fd != original_output_fd)
                safe_close_above_stdio(original_error_fd);

        /* Close the copies we moved > 2 */
        for (i = 0; i < 3; i++)
                safe_close(copy_fd[i]);

        /* Close our null fd, if it's > 2 */
        safe_close_above_stdio(null_fd);

        return r;
}