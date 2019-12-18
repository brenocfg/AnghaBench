#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct msghdr {size_t msg_iovlen; size_t member_1; struct iovec* member_0; struct iovec* msg_iov; } ;
struct iovec {int dummy; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_4__ {int digest_valid; int /*<<< orphan*/  fd; } ;
typedef  TYPE_1__ khash ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_MORE ; 
 int /*<<< orphan*/  assert (TYPE_1__*) ; 
 int errno ; 
 scalar_t__ sendmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

int khash_put_iovec(khash *h, const struct iovec *iovec, size_t n) {
        struct msghdr mh = {
                mh.msg_iov = (struct iovec*) iovec,
                mh.msg_iovlen = n,
        };
        ssize_t k;

        assert(h);
        assert(iovec || n == 0);

        if (n <= 0)
                return 0;

        k = sendmsg(h->fd, &mh, MSG_MORE);
        if (k < 0)
                return -errno;

        h->digest_valid = false;

        return 0;
}