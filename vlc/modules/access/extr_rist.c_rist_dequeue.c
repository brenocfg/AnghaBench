#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_7__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  size_t uint16_t ;
struct rtp_pkt {TYPE_7__* buffer; scalar_t__ rtp_ts; } ;
struct rist_flow {size_t ri; size_t wi; scalar_t__ reset; scalar_t__ hi_timestamp; scalar_t__ rtp_latency; struct rtp_pkt* buffer; } ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_10__ {int b_flag_discontinuity; int /*<<< orphan*/  i_lost_packets; } ;
typedef  TYPE_2__ stream_sys_t ;
struct TYPE_11__ {int i_buffer; int /*<<< orphan*/  p_buffer; } ;
typedef  TYPE_3__ block_t ;
struct TYPE_12__ {int i_buffer; int p_buffer; } ;

/* Variables and functions */
 int RTP_HEADER_SIZE ; 
 TYPE_3__* block_Alloc (int) ; 
 int /*<<< orphan*/  block_Release (TYPE_7__*) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_1__*,char*,size_t,size_t,size_t) ; 

__attribute__((used)) static block_t *rist_dequeue(stream_t *p_access, struct rist_flow *flow)
{
    stream_sys_t *p_sys = p_access->p_sys;
    block_t *pktout = NULL;
    struct rtp_pkt *pkt;
    uint16_t idx;
    if (flow->ri == flow->wi || flow->reset > 0)
        return NULL;

    idx = flow->ri;
    bool found_data = false;
    uint16_t loss_amount = 0;
    while(idx++ != flow->wi) {

        pkt = &(flow->buffer[idx]);
        if (!pkt->buffer)
        {
            /*msg_Info(p_access, "Possible packet loss on index #%d", idx);*/
            loss_amount++;
            /* We move ahead until we find a timestamp but we do not move the cursor.
             * None of them are guaranteed packet loss because we do not really
             * know their timestamps. They might still arrive on the next loop.
             * We can confirm the loss only if we get a valid packet in the loop below. */
            continue;
        }

        /*printf("IDX=%d, flow->hi_timestamp: %u, (ts + flow->rtp_latency): %u\n", idx,
            flow->hi_timestamp, (ts - 100 * flow->qdelay));*/
        if (flow->hi_timestamp > (uint32_t)(pkt->rtp_ts + flow->rtp_latency))
        {
            /* Populate output packet now but remove rtp header from source */
            int newSize = pkt->buffer->i_buffer - RTP_HEADER_SIZE;
            pktout = block_Alloc(newSize);
            if (pktout)
            {
                pktout->i_buffer = newSize;
                memcpy(pktout->p_buffer, pkt->buffer->p_buffer + RTP_HEADER_SIZE, newSize);
                /* free the buffer and increase the read index */
                flow->ri = idx;
                /* TODO: calculate average duration using buffer average (bring from sender) */
                found_data = true;
            }
            block_Release(pkt->buffer);
            pkt->buffer = NULL;
            break;
        }

    }

    if (loss_amount > 0 && found_data == true)
    {
        /* Packet loss confirmed, we found valid data after the holes */
        msg_Dbg(p_access, "Packet NOT RECOVERED, %d packet(s), Window: [%d:%d]", loss_amount,
            flow->ri, flow->wi);
        p_sys->i_lost_packets += loss_amount;
        p_sys->b_flag_discontinuity = true;
    }

    return pktout;
}