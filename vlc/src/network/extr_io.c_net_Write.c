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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int ssize_t ;

/* Variables and functions */
 scalar_t__ EAGAIN ; 
 scalar_t__ EINTR ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlc_killed () ; 
 int vlc_send_i11e (int,void const*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_strerror_c (scalar_t__) ; 
 int /*<<< orphan*/  vlc_testcancel () ; 

ssize_t (net_Write)(vlc_object_t *obj, int fd, const void *buf, size_t len)
{
    size_t written = 0;

    do
    {
        if (vlc_killed())
        {
            vlc_testcancel();
            errno = EINTR;
            return -1;
        }

        ssize_t val = vlc_send_i11e (fd, buf, len, MSG_NOSIGNAL);
        if (val == -1)
        {
            if (errno == EINTR || errno == EAGAIN)
                continue;

            msg_Err(obj, "write error: %s", vlc_strerror_c(errno));
            return written ? (ssize_t)written : -1;
        }

        if (val == 0)
            break;

        written += val;
        assert(len >= (size_t)val);
        len -= val;
        buf = ((const char *)buf) + val;
    }
    while (len > 0);

    return written;
}