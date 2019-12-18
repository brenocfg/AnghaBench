#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_tick_t ;
struct pollfd {int fd; int revents; int /*<<< orphan*/  events; } ;
struct msghdr {int msg_iovlen; int msg_flags; struct iovec* msg_iov; } ;
struct iovec {int iov_len; int /*<<< orphan*/  iov_base; } ;
typedef  int ssize_t ;
struct TYPE_11__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_12__ {int fd; int /*<<< orphan*/  session; } ;
typedef  TYPE_2__ demux_sys_t ;
struct TYPE_13__ {int i_buffer; int /*<<< orphan*/  i_flags; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCK_FLAG_CORRUPTED ; 
 int DEFAULT_MRU ; 
 int MSG_TRUNC ; 
 int POLLHUP ; 
 int /*<<< orphan*/  POLLIN ; 
 int /*<<< orphan*/  VLC_TICK_INVALID ; 
 TYPE_3__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int,int) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int poll (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int recvmsg (int,struct msghdr*,int const) ; 
 int /*<<< orphan*/  rtp_dequeue (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_process (TYPE_1__*,TYPE_3__*) ; 
 int /*<<< orphan*/  rtp_timeout (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

void *rtp_dgram_thread (void *opaque)
{
    demux_t *demux = opaque;
    demux_sys_t *sys = demux->p_sys;
    vlc_tick_t deadline = VLC_TICK_INVALID;
    int rtp_fd = sys->fd;
#ifdef __linux__
    const int trunc_flag = MSG_TRUNC;
#else
    const int trunc_flag = 0;
#endif

    struct iovec iov =
    {
        .iov_len = DEFAULT_MRU,
    };
    struct msghdr msg =
    {
        .msg_iov = &iov,
        .msg_iovlen = 1,
    };

    struct pollfd ufd[1];
    ufd[0].fd = rtp_fd;
    ufd[0].events = POLLIN;

    for (;;)
    {
        int n = poll (ufd, 1, rtp_timeout (deadline));
        if (n == -1)
            continue;

        int canc = vlc_savecancel ();
        if (n == 0)
            goto dequeue;

        if (ufd[0].revents)
        {
            n--;
            if (unlikely(ufd[0].revents & POLLHUP))
                break; /* RTP socket dead (DCCP only) */

            block_t *block = block_Alloc (iov.iov_len);
            if (unlikely(block == NULL))
            {
                if (iov.iov_len == DEFAULT_MRU)
                    break; /* we are totallly screwed */
                iov.iov_len = DEFAULT_MRU;
                continue; /* retry with shrunk MRU */
            }

            iov.iov_base = block->p_buffer;
            msg.msg_flags = trunc_flag;

            ssize_t len = recvmsg (rtp_fd, &msg, trunc_flag);
            if (len != -1)
            {
                if (msg.msg_flags & trunc_flag)
                {
                    msg_Err(demux, "%zd bytes packet truncated (MRU was %zu)",
                            len, iov.iov_len);
                    block->i_flags |= BLOCK_FLAG_CORRUPTED;
                    iov.iov_len = len;
                }
                else
                    block->i_buffer = len;

                rtp_process (demux, block);
            }
            else
            {
                msg_Warn (demux, "RTP network error: %s",
                          vlc_strerror_c(errno));
                block_Release (block);
            }
        }

    dequeue:
        if (!rtp_dequeue (demux, sys->session, &deadline))
            deadline = VLC_TICK_INVALID;
        vlc_restorecancel (canc);
    }
    return NULL;
}