#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct rtp_pkt {scalar_t__ fd_out; scalar_t__ fd_rtcp; scalar_t__ fd_rtcp_m; struct rtp_pkt* buffer; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_5__ {struct rtp_pkt* p_pktbuffer; int /*<<< orphan*/  fd_lock; int /*<<< orphan*/  lock; struct rtp_pkt* flow; int /*<<< orphan*/ * p_fifo; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;

/* Variables and functions */
 int RIST_QUEUE_SIZE ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_Release (struct rtp_pkt*) ; 
 int /*<<< orphan*/  free (struct rtp_pkt*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_Close (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Clean( sout_access_out_t *p_access )
{
    sout_access_out_sys_t *p_sys = p_access->p_sys;

    if( likely(p_sys->p_fifo != NULL) )
        block_FifoRelease( p_sys->p_fifo );

    if ( p_sys->flow )
    {
        if (p_sys->flow->fd_out >= 0) {
            net_Close (p_sys->flow->fd_out);
        }
        if (p_sys->flow->fd_rtcp >= 0) {
            net_Close (p_sys->flow->fd_rtcp);
        }
        if (p_sys->flow->fd_rtcp_m >= 0) {
            net_Close (p_sys->flow->fd_rtcp_m);
        }
        for (int i=0; i<RIST_QUEUE_SIZE; i++) {
            struct rtp_pkt *pkt = &(p_sys->flow->buffer[i]);
            if (pkt->buffer)
            {
                block_Release(pkt->buffer);
                pkt->buffer = NULL;
            }
        }
        free(p_sys->flow->buffer);
        free(p_sys->flow);
    }

    vlc_mutex_destroy( &p_sys->lock );
    vlc_mutex_destroy( &p_sys->fd_lock );
    if (p_sys->p_pktbuffer)
        block_Release(p_sys->p_pktbuffer);
}