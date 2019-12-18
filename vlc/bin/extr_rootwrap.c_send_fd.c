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
struct cmsghdr {int cmsg_len; int /*<<< orphan*/  cmsg_type; int /*<<< orphan*/  cmsg_level; } ;
typedef  int /*<<< orphan*/  fd ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 struct cmsghdr* CMSG_FIRSTHDR (struct msghdr*) ; 
 int CMSG_LEN (int) ; 
 int CMSG_SPACE (int) ; 
 int /*<<< orphan*/  MSG_NOSIGNAL ; 
 int /*<<< orphan*/  SCM_RIGHTS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int*,int) ; 
 int sendmsg (int,struct msghdr*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int send_fd (int p, int fd)
{
    struct msghdr hdr;
    struct iovec iov;
    struct cmsghdr *cmsg;
    char buf[CMSG_SPACE (sizeof (fd))];
    int val = 0;

    hdr.msg_name = NULL;
    hdr.msg_namelen = 0;
    hdr.msg_iov = &iov;
    hdr.msg_iovlen = 1;
    hdr.msg_control = buf;
    hdr.msg_controllen = sizeof (buf);

    iov.iov_base = &val;
    iov.iov_len = sizeof (val);

    cmsg = CMSG_FIRSTHDR (&hdr);
    cmsg->cmsg_level = SOL_SOCKET;
    cmsg->cmsg_type = SCM_RIGHTS;
    cmsg->cmsg_len = CMSG_LEN (sizeof (fd));
    memcpy (CMSG_DATA (cmsg), &fd, sizeof (fd));
    hdr.msg_controllen = cmsg->cmsg_len;

    return sendmsg(p, &hdr, MSG_NOSIGNAL) == sizeof (val) ? 0 : -1;
}