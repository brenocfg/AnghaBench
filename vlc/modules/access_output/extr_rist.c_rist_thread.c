#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_5__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  scalar_t__ uint64_t ;
struct pollfd {int fd; int events; int revents; } ;
typedef  int ssize_t ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_8__ {scalar_t__ last_rtcp_tx; TYPE_5__* flow; scalar_t__ b_ismulticast; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_9__ {int fd_rtcp; int fd_rtcp_m; } ;

/* Variables and functions */
 int POLLIN ; 
 int RTCP_INTERVAL ; 
 int RTP_PKT_SIZE ; 
 scalar_t__ VLC_TICK_FROM_MS (int) ; 
 int /*<<< orphan*/  errno ; 
 int gai_strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,int,int) ; 
 int poll (struct pollfd*,int,int) ; 
 int rist_Read (int,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rist_rtcp_recv (TYPE_1__*,TYPE_5__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rist_rtcp_send (TYPE_1__*) ; 
 scalar_t__ unlikely (int) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 scalar_t__ vlc_tick_now () ; 

__attribute__((used)) static void *rist_thread(void *data)
{
    sout_access_out_t *p_access = data;
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    uint64_t now;
    uint8_t pkt[RTP_PKT_SIZE];
    struct pollfd pfd[2];
    int ret;
    ssize_t r;

    int poll_sockets = 1;
    pfd[0].fd = p_sys->flow->fd_rtcp;
    pfd[0].events = POLLIN;
    if (p_sys->b_ismulticast)
    {
        pfd[1].fd = p_sys->flow->fd_rtcp_m;
        pfd[1].events = POLLIN;
        poll_sockets++;
    }

    for (;;) {
        ret = poll(pfd, poll_sockets, RTCP_INTERVAL >> 1);
        int canc = vlc_savecancel();
        if (ret > 0)
        {
            if (pfd[0].revents & POLLIN)
            {
                r = rist_Read(p_sys->flow->fd_rtcp, pkt, RTP_PKT_SIZE);
                if (r == RTP_PKT_SIZE) {
                    msg_Err(p_access, "Rist RTCP messsage is too big (%zd bytes) and was probably " \
                        "cut, please keep it under %d bytes", r, RTP_PKT_SIZE);
                }
                if (unlikely(r == -1)) {
                    msg_Err(p_access, "socket %d error: %s\n", p_sys->flow->fd_rtcp, 
                        gai_strerror(errno));
                }
                else {
                    rist_rtcp_recv(p_access, p_sys->flow, pkt, r);
                }
            }
            if (p_sys->b_ismulticast && (pfd[1].revents & POLLIN))
            {
                r = rist_Read(p_sys->flow->fd_rtcp_m, pkt, RTP_PKT_SIZE);
                if (r == RTP_PKT_SIZE) {
                    msg_Err(p_access, "Rist RTCP messsage is too big (%zd bytes) and was " \
                        "probably cut, please keep it under %d bytes", r, RTP_PKT_SIZE);
                }
                if (unlikely(r == -1)) {
                    msg_Err(p_access, "mcast socket %d error: %s\n", p_sys->flow->fd_rtcp_m,
                        gai_strerror(errno));
                }
                else {
                    rist_rtcp_recv(p_access, p_sys->flow, pkt, r);
                }
            }
        }

        /* And, in any case: */
        now = vlc_tick_now();
        if ((now - p_sys->last_rtcp_tx) > VLC_TICK_FROM_MS(RTCP_INTERVAL))
        {
            rist_rtcp_send(p_access);
            p_sys->last_rtcp_tx = now;
        }
        vlc_restorecancel (canc);
    }

    return NULL;
}