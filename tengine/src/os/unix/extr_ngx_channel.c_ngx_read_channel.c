#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct msghdr {int msg_iovlen; int msg_controllen; int msg_accrightslen; int msg_flags; void* msg_accrights; void* msg_control; struct iovec* msg_iov; scalar_t__ msg_namelen; int /*<<< orphan*/ * msg_name; } ;
struct iovec {char* iov_base; size_t iov_len; } ;
struct cmsghdr {scalar_t__ cmsg_len; scalar_t__ cmsg_type; int /*<<< orphan*/  cmsg_level; } ;
typedef  int ssize_t ;
typedef  scalar_t__ socklen_t ;
typedef  int /*<<< orphan*/  ngx_socket_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int ngx_int_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_3__ {scalar_t__ command; int fd; } ;
typedef  TYPE_1__ ngx_channel_t ;
typedef  int /*<<< orphan*/  cmsg ;
typedef  void* caddr_t ;

/* Variables and functions */
 int /*<<< orphan*/  CMSG_DATA (struct cmsghdr*) ; 
 scalar_t__ CMSG_LEN (int) ; 
 int CMSG_SPACE (int) ; 
 int MSG_CTRUNC ; 
 int MSG_TRUNC ; 
 int NGX_AGAIN ; 
 scalar_t__ NGX_CMD_OPEN_CHANNEL ; 
 scalar_t__ NGX_EAGAIN ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 scalar_t__ SCM_RIGHTS ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 scalar_t__ ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (int*,int /*<<< orphan*/ ,int) ; 
 int recvmsg (int /*<<< orphan*/ ,struct msghdr*,int /*<<< orphan*/ ) ; 

ngx_int_t
ngx_read_channel(ngx_socket_t s, ngx_channel_t *ch, size_t size, ngx_log_t *log)
{
    ssize_t             n;
    ngx_err_t           err;
    struct iovec        iov[1];
    struct msghdr       msg;

#if (NGX_HAVE_MSGHDR_MSG_CONTROL)
    union {
        struct cmsghdr  cm;
        char            space[CMSG_SPACE(sizeof(int))];
    } cmsg;
#else
    int                 fd;
#endif

    iov[0].iov_base = (char *) ch;
    iov[0].iov_len = size;

    msg.msg_name = NULL;
    msg.msg_namelen = 0;
    msg.msg_iov = iov;
    msg.msg_iovlen = 1;

#if (NGX_HAVE_MSGHDR_MSG_CONTROL)
    msg.msg_control = (caddr_t) &cmsg;
    msg.msg_controllen = sizeof(cmsg);
#else
    msg.msg_accrights = (caddr_t) &fd;
    msg.msg_accrightslen = sizeof(int);
#endif

    n = recvmsg(s, &msg, 0);

    if (n == -1) {
        err = ngx_errno;
        if (err == NGX_EAGAIN) {
            return NGX_AGAIN;
        }

        ngx_log_error(NGX_LOG_ALERT, log, err, "recvmsg() failed");
        return NGX_ERROR;
    }

    if (n == 0) {
        ngx_log_debug0(NGX_LOG_DEBUG_CORE, log, 0, "recvmsg() returned zero");
        return NGX_ERROR;
    }

    if ((size_t) n < sizeof(ngx_channel_t)) {
        ngx_log_error(NGX_LOG_ALERT, log, 0,
                      "recvmsg() returned not enough data: %z", n);
        return NGX_ERROR;
    }

#if (NGX_HAVE_MSGHDR_MSG_CONTROL)

    if (ch->command == NGX_CMD_OPEN_CHANNEL) {

        if (cmsg.cm.cmsg_len < (socklen_t) CMSG_LEN(sizeof(int))) {
            ngx_log_error(NGX_LOG_ALERT, log, 0,
                          "recvmsg() returned too small ancillary data");
            return NGX_ERROR;
        }

        if (cmsg.cm.cmsg_level != SOL_SOCKET || cmsg.cm.cmsg_type != SCM_RIGHTS)
        {
            ngx_log_error(NGX_LOG_ALERT, log, 0,
                          "recvmsg() returned invalid ancillary data "
                          "level %d or type %d",
                          cmsg.cm.cmsg_level, cmsg.cm.cmsg_type);
            return NGX_ERROR;
        }

        /* ch->fd = *(int *) CMSG_DATA(&cmsg.cm); */

        ngx_memcpy(&ch->fd, CMSG_DATA(&cmsg.cm), sizeof(int));
    }

    if (msg.msg_flags & (MSG_TRUNC|MSG_CTRUNC)) {
        ngx_log_error(NGX_LOG_ALERT, log, 0,
                      "recvmsg() truncated data");
    }

#else

    if (ch->command == NGX_CMD_OPEN_CHANNEL) {
        if (msg.msg_accrightslen != sizeof(int)) {
            ngx_log_error(NGX_LOG_ALERT, log, 0,
                          "recvmsg() returned no ancillary data");
            return NGX_ERROR;
        }

        ch->fd = fd;
    }

#endif

    return n;
}