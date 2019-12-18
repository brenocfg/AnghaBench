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
struct rtp_pkt {scalar_t__ fd_in; scalar_t__ fd_nack; scalar_t__ fd_rtcp_m; scalar_t__ i_buffer; struct rtp_pkt* buffer; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; struct rtp_pkt* flow; int /*<<< orphan*/ * p_fifo; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int RIST_QUEUE_SIZE ; 
 int /*<<< orphan*/  block_FifoRelease (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  block_Release (struct rtp_pkt*) ; 
 int /*<<< orphan*/  free (struct rtp_pkt*) ; 
 scalar_t__ likely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_Close (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_destroy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void Clean( stream_t *p_access )
{
    stream_sys_t *p_sys = p_access->p_sys;

    if( likely(p_sys->p_fifo != NULL) )
        block_FifoRelease( p_sys->p_fifo );

    if (p_sys->flow)
    {
        if (p_sys->flow->fd_in >= 0)
            net_Close (p_sys->flow->fd_in);
        if (p_sys->flow->fd_nack >= 0)
            net_Close (p_sys->flow->fd_nack);
        if (p_sys->flow->fd_rtcp_m >= 0)
            net_Close (p_sys->flow->fd_rtcp_m);
        for (int i=0; i<RIST_QUEUE_SIZE; i++) {
            struct rtp_pkt *pkt = &(p_sys->flow->buffer[i]);
            if (pkt->buffer && pkt->buffer->i_buffer > 0) {
                block_Release(pkt->buffer);
                pkt->buffer = NULL;
            }
        }
        free(p_sys->flow->buffer);
        free(p_sys->flow);
    }

    vlc_mutex_destroy( &p_sys->lock );
}