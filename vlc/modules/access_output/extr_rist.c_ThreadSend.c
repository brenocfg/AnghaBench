#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ vlc_tick_t ;
typedef  scalar_t__ uint64_t ;
typedef  void* uint32_t ;
typedef  int uint16_t ;
struct rtp_pkt {TYPE_3__* buffer; void* rtp_ts; } ;
struct rist_flow {int reset; int wi; int last_out; int /*<<< orphan*/  bytes_count; int /*<<< orphan*/  packets_count; void* hi_timestamp; struct rtp_pkt* buffer; int /*<<< orphan*/  fd_out; } ;
typedef  scalar_t__ ssize_t ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_10__ {scalar_t__ i_last_stat; scalar_t__ i_retransmit_packets; scalar_t__ i_total_packets; int /*<<< orphan*/  lock; int /*<<< orphan*/  fd_lock; int /*<<< orphan*/  p_fifo; struct rist_flow* flow; scalar_t__ i_ticks_caching; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_11__ {scalar_t__ i_buffer; int /*<<< orphan*/  p_buffer; scalar_t__ i_dts; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  STATS_INTERVAL ; 
 scalar_t__ VLC_TICK_FROM_MS (int /*<<< orphan*/ ) ; 
 TYPE_3__* block_FifoGet (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  block_Release (TYPE_3__*) ; 
 int /*<<< orphan*/  block_cleanup_push (TYPE_3__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*,...) ; 
 scalar_t__ rist_Write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int rtp_get_seqnum (int /*<<< orphan*/ ) ; 
 void* rtp_get_timestamp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cleanup_pop () ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_restorecancel (int) ; 
 int vlc_savecancel () ; 
 scalar_t__ vlc_tick_now () ; 
 int /*<<< orphan*/  vlc_tick_wait (scalar_t__) ; 

__attribute__((used)) static void* ThreadSend( void *data )
{
    sout_access_out_t *p_access = data;
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    vlc_tick_t i_caching = p_sys->i_ticks_caching;
    struct rist_flow *flow = p_sys->flow;

    for (;;)
    {
        ssize_t len = 0;
        uint16_t seq = 0;
        uint32_t pkt_ts = 0;
        block_t *out = block_FifoGet( p_sys->p_fifo );

        block_cleanup_push( out );
        vlc_tick_wait (out->i_dts + i_caching);
        vlc_cleanup_pop();

        len = out->i_buffer;
        int canc = vlc_savecancel();

        seq = rtp_get_seqnum(out->p_buffer);
        pkt_ts = rtp_get_timestamp(out->p_buffer);

        vlc_mutex_lock( &p_sys->fd_lock );
#ifdef TEST_PACKET_LOSS
#   warning COMPILED WITH SELF INFLICTED PACKET LOSS
        if ((seq % 14) == 0) {
            /*msg_Err(p_access, "Dropped packet with seq number %d ...", seq);*/
        }
        else
        {
            if (rist_Write(flow->fd_out, out->p_buffer, len) != len) {
                msg_Err(p_access, "Error sending data packet after 2 tries ...");
            }
        }
#else
        if (rist_Write(flow->fd_out, out->p_buffer, len) != len) {
            msg_Err(p_access, "Error sending data packet after 2 tries ...");
        }
#endif
        vlc_mutex_unlock( &p_sys->fd_lock );

        /* Insert Into Queue */
        vlc_mutex_lock( &p_sys->lock );
        /* Always replace the existing one with the new one */
        struct rtp_pkt *pkt;
        pkt = &(flow->buffer[seq]);
        if (pkt->buffer)
        {
            block_Release(pkt->buffer);
            pkt->buffer = NULL;
        }
        pkt->rtp_ts = pkt_ts;
        pkt->buffer = out;

        if (flow->reset == 1)
        {
            msg_Info(p_access, "Traffic detected");
            /* First packet in the queue */
            flow->reset = 0;
        }
        flow->wi = seq;
        flow->hi_timestamp = pkt_ts;
        /* Stats for RTCP feedback packets */
        flow->packets_count++;
        flow->bytes_count += len;
        flow->last_out = seq;
        vlc_mutex_unlock( &p_sys->lock );

        /* We print out the stats once per second */
        uint64_t now = vlc_tick_now();
        uint64_t interval = (now - p_sys->i_last_stat);
        if ( interval > VLC_TICK_FROM_MS(STATS_INTERVAL) )
        {
            if (p_sys->i_retransmit_packets > 0)
            {
                float quality = 100;
                if (p_sys->i_total_packets > 0)
                    quality = (float)100 - (float)100*(float)(p_sys->i_retransmit_packets)
                        /(float)p_sys->i_total_packets;
                msg_Info(p_access, "STATS: Total %u, Retransmitted %u, Link Quality %.2f%%", 
                    p_sys->i_total_packets, p_sys->i_retransmit_packets, quality);
            }
            p_sys->i_last_stat = now;
            p_sys->i_retransmit_packets = 0;
            p_sys->i_total_packets = 0;
        }
        p_sys->i_total_packets++;

        vlc_restorecancel (canc);
    }
    return NULL;
}