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
struct sockaddr {int dummy; } ;
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  socklen_t ;

/* Variables and functions */
#define  EAGAIN 129 
#define  EINTR 128 
 int errno ; 
 int /*<<< orphan*/  vlc_killed () ; 
 int vlc_recv_i11e (int,void*,size_t,int /*<<< orphan*/ ) ; 
 int vlc_recvfrom_i11e (int,void*,size_t,int /*<<< orphan*/ ,struct sockaddr*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline ssize_t rist_ReadFrom_i11e(int fd, void *buf, size_t len, struct sockaddr *peer, 
    socklen_t *slen)
{
    ssize_t ret = -1;

    if (peer == NULL)
        ret = vlc_recv_i11e(fd, buf, len, 0);
    else
        ret = vlc_recvfrom_i11e(fd, buf, len, 0, peer, slen);

    if (ret == -1)
    {
        switch (errno)
        {
        case EAGAIN:
        case EINTR:
            if (vlc_killed())
                return ret;

            /* retry one time */
            if (peer == NULL)
                ret = vlc_recv_i11e(fd, buf, len, 0);
            else
                ret = vlc_recvfrom_i11e(fd, buf, len, 0, peer, slen);
        default:
            break;
        }
    }
    return ret;
}