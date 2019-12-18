#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {TYPE_1__* ops; } ;
typedef  TYPE_2__ vlc_tls_t ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct iovec {char* iov_base; size_t iov_len; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_6__ {scalar_t__ (* writev ) (TYPE_2__*,struct iovec*,int) ;} ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  POLLOUT ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  poll (struct pollfd*,int,int) ; 
 scalar_t__ stub1 (TYPE_2__*,struct iovec*,int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_tls_GetPollFD (TYPE_2__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t vlc_https_send(vlc_tls_t *tls, const void *buf, size_t len)
{
    struct iovec iov;
    size_t count = 0;

    iov.iov_base = (void *)buf;
    iov.iov_len = len;

    while (count < len)
    {
        int canc = vlc_savecancel();
        ssize_t val = tls->ops->writev(tls, &iov, 1);

        vlc_restorecancel(canc);

        if (val > 0)
        {
            iov.iov_base = (char *)iov.iov_base + val;
            iov.iov_len -= val;
            count += val;
            continue;
        }

        if (val == 0)
            break;

        if (errno != EINTR && errno != EAGAIN)
            return count ? (ssize_t)count : -1;

        struct pollfd ufd;

        ufd.events = POLLOUT;
        ufd.fd = vlc_tls_GetPollFD(tls, &ufd.events);
        poll(&ufd, 1, -1);
    }

    return count;
}