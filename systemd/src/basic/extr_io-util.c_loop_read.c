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
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 scalar_t__ EINVAL ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ SSIZE_MAX ; 
 int /*<<< orphan*/  USEC_INFINITY ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  fd_wait_for_event (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ read (int,int /*<<< orphan*/ *,size_t) ; 

ssize_t loop_read(int fd, void *buf, size_t nbytes, bool do_poll) {
        uint8_t *p = buf;
        ssize_t n = 0;

        assert(fd >= 0);
        assert(buf);

        /* If called with nbytes == 0, let's call read() at least
         * once, to validate the operation */

        if (nbytes > (size_t) SSIZE_MAX)
                return -EINVAL;

        do {
                ssize_t k;

                k = read(fd, p, nbytes);
                if (k < 0) {
                        if (errno == EINTR)
                                continue;

                        if (errno == EAGAIN && do_poll) {

                                /* We knowingly ignore any return value here,
                                 * and expect that any error/EOF is reported
                                 * via read() */

                                (void) fd_wait_for_event(fd, POLLIN, USEC_INFINITY);
                                continue;
                        }

                        return n > 0 ? n : -errno;
                }

                if (k == 0)
                        return n;

                assert((size_t) k <= nbytes);

                p += k;
                nbytes -= k;
                n += k;
        } while (nbytes > 0);

        return n;
}