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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ ssize_t ;

/* Variables and functions */
 int EAGAIN ; 
 int EINTR ; 
 int EINVAL ; 
 int EIO ; 
 int /*<<< orphan*/  POLLOUT ; 
 scalar_t__ SSIZE_MAX ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 scalar_t__ _unlikely_ (int) ; 
 int /*<<< orphan*/  assert (int) ; 
 int errno ; 
 int /*<<< orphan*/  fd_wait_for_event (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write (int,int /*<<< orphan*/  const*,size_t) ; 

int loop_write(int fd, const void *buf, size_t nbytes, bool do_poll) {
        const uint8_t *p = buf;

        assert(fd >= 0);
        assert(buf);

        if (_unlikely_(nbytes > (size_t) SSIZE_MAX))
                return -EINVAL;

        do {
                ssize_t k;

                k = write(fd, p, nbytes);
                if (k < 0) {
                        if (errno == EINTR)
                                continue;

                        if (errno == EAGAIN && do_poll) {
                                /* We knowingly ignore any return value here,
                                 * and expect that any error/EOF is reported
                                 * via write() */

                                (void) fd_wait_for_event(fd, POLLOUT, USEC_INFINITY);
                                continue;
                        }

                        return -errno;
                }

                if (_unlikely_(nbytes > 0 && k == 0)) /* Can't really happen */
                        return -EIO;

                assert((size_t) k <= nbytes);

                p += k;
                nbytes -= k;
        } while (nbytes > 0);

        return 0;
}