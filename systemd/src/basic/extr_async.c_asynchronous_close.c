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
 int /*<<< orphan*/  EBADF ; 
 int /*<<< orphan*/  FD_TO_PTR (int) ; 
 int /*<<< orphan*/  PROTECT_ERRNO ; 
 int /*<<< orphan*/  assert_se (int) ; 
 int asynchronous_job (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  close_nointr (int) ; 
 int /*<<< orphan*/  close_thread ; 

int asynchronous_close(int fd) {
        int r;

        /* This is supposed to behave similar to safe_close(), but
         * actually invoke close() asynchronously, so that it will
         * never block. Ideally the kernel would have an API for this,
         * but it doesn't, so we work around it, and hide this as a
         * far away as we can. */

        if (fd >= 0) {
                PROTECT_ERRNO;

                r = asynchronous_job(close_thread, FD_TO_PTR(fd));
                if (r < 0)
                         assert_se(close_nointr(fd) != -EBADF);
        }

        return -1;
}