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
struct vlc_tls {int dummy; } ;
struct iovec {size_t iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  size_t ssize_t ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t,size_t) ; 
 size_t stream_content ; 
 size_t stream_length ; 

__attribute__((used)) static ssize_t recv_callback(struct vlc_tls *tls, struct iovec *iov,
                             unsigned count)
{
    size_t rcvd = 0;

    while (count > 0)
    {
        size_t copy = iov->iov_len;
        if (copy > stream_length)
            copy = stream_length;

        if (copy > 0)
        {
            memcpy(iov->iov_base, stream_content, copy);
            stream_content += copy;
            stream_length -= copy;
            rcvd += copy;
        }

        iov++;
        count--;
    }
    (void) tls;
    return rcvd;
}