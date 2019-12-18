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
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int /*<<< orphan*/  uint32_t ;
typedef  int /*<<< orphan*/  uint16_t ;
struct TYPE_9__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_10__ {int /*<<< orphan*/  p_fifo; int /*<<< orphan*/  ssrc; int /*<<< orphan*/  rtp_counter; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
struct TYPE_11__ {int /*<<< orphan*/  i_dts; int /*<<< orphan*/ * p_buffer; } ;
typedef  TYPE_3__ block_t ;

/* Variables and functions */
 int /*<<< orphan*/  MPEG_II_TRANSPORT_STREAM ; 
 TYPE_3__* block_Duplicate (TYPE_3__*) ; 
 int /*<<< orphan*/  block_FifoPut (int /*<<< orphan*/ ,TYPE_3__*) ; 
 int /*<<< orphan*/  rtp_get_ts (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_set_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtp_set_int_ssrc (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_set_seqnum (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_set_timestamp (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtp_set_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void SendtoFIFO( sout_access_out_t *p_access, block_t *buffer )
{
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    uint16_t seq = p_sys->rtp_counter++;

    /* Set fresh rtp header data */
    uint8_t *bufhdr = buffer->p_buffer;
    rtp_set_hdr(bufhdr);
    rtp_set_type(bufhdr, MPEG_II_TRANSPORT_STREAM);
    rtp_set_seqnum(bufhdr, seq);
    rtp_set_int_ssrc(bufhdr, p_sys->ssrc);
    uint32_t pkt_ts = rtp_get_ts(buffer->i_dts);
    rtp_set_timestamp(bufhdr, pkt_ts);

    block_t *pkt = block_Duplicate(buffer);
    block_FifoPut( p_sys->p_fifo, pkt );
}