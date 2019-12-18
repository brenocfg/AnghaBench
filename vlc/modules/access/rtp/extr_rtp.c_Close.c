#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct TYPE_5__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ demux_t ;
struct TYPE_6__ {int rtcp_fd; int fd; scalar_t__ session; scalar_t__ srtp; int /*<<< orphan*/  thread; scalar_t__ thread_ready; } ;
typedef  TYPE_2__ demux_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  free (TYPE_2__*) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int /*<<< orphan*/  rtp_session_destroy (TYPE_1__*,scalar_t__) ; 
 int /*<<< orphan*/  srtp_destroy (scalar_t__) ; 
 int /*<<< orphan*/  vlc_cancel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Close (vlc_object_t *obj)
{
    demux_t *demux = (demux_t *)obj;
    demux_sys_t *p_sys = demux->p_sys;

    if (p_sys->thread_ready)
    {
        vlc_cancel (p_sys->thread);
        vlc_join (p_sys->thread, NULL);
    }

#ifdef HAVE_SRTP
    if (p_sys->srtp)
        srtp_destroy (p_sys->srtp);
#endif
    if (p_sys->session)
        rtp_session_destroy (demux, p_sys->session);
    if (p_sys->rtcp_fd != -1)
        net_Close (p_sys->rtcp_fd);
    net_Close (p_sys->fd);
    free (p_sys);
}