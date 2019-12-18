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
typedef  int /*<<< orphan*/  val ;
struct msghdr {int msg_iovlen; char* msg_control; int msg_controllen; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {int* iov_base; int iov_len; } ;
struct cmsghdr {scalar_t__ cmsg_level; scalar_t__ cmsg_type; scalar_t__ cmsg_len; } ;
typedef  int /*<<< orphan*/  fd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 scalar_t__ CMSG_LEN (int) ; 
 struct cmsghdr* CMSG_NXTHDR (struct msghdr*,struct cmsghdr*) ; 
 int CMSG_SPACE (int) ; 
 scalar_t__ SCM_RIGHTS ; 
 scalar_t__ SOL_SOCKET ; 
 int errno ; 
 int /*<<< orphan*/  memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int recv_fd (int p)
{
    struct msghdr hdr;
    struct iovec iov;
    struct cmsghdr *cmsg;
    int val, fd;
    char buf[CMSG_SPACE (sizeof (fd))];

    hdr.msg_name = NULL;
    hdr.msg_namelen = 0;
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = buf;
    hdr.msg_controllen = sizeof (buf);

    iov.iov_base = &val;
    iov.iov_len = sizeof (val);

    if (recvmsg (p, &hdr, 0) != sizeof (val))
        return -1;

    for (cmsg = CMSG_FIRSTHDR (&hdr); cmsg != NULL;
         cmsg = CMSG_NXTHDR (&hdr, cmsg))
    {
        if ((cmsg->cmsg_level == SOL_SOCKET)
         && (cmsg->cmsg_type == SCM_RIGHTS)
         && (cmsg->cmsg_len >= CMSG_LEN (sizeof (fd))))
        {
            memcpy (&fd, CMSG_DATA (cmsg), sizeof (fd));
            return fd;
        }
    }

    errno = val;
    return -1;
}