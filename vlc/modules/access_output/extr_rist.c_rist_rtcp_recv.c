#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;
struct rist_flow {int dummy; } ;
struct TYPE_7__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ sout_access_out_t ;
struct TYPE_8__ {int b_ismulticast; int /*<<< orphan*/  receiver_name; } ;
typedef  TYPE_2__ sout_access_out_sys_t ;
typedef  size_t int8_t ;

/* Variables and functions */
#define  RTCP_PT_RR 132 
#define  RTCP_PT_RTPFB 131 
#define  RTCP_PT_RTPFR 130 
#define  RTCP_PT_SDES 129 
#define  RTCP_PT_SR 128 
 int /*<<< orphan*/  RTCP_SDES_SIZE ; 
 int /*<<< orphan*/  memcmp (size_t*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,size_t*,size_t) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,size_t,...) ; 
 int /*<<< orphan*/  msg_Info (TYPE_1__*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  process_nack (TYPE_1__*,size_t,size_t,struct rist_flow*,size_t*) ; 
 size_t rtcp_get_length (size_t*) ; 
 size_t rtcp_get_pt (size_t*) ; 
 size_t rtcp_sdes_get_name_length (size_t*) ; 
 int /*<<< orphan*/  rtp_check_hdr (size_t*) ; 

__attribute__((used)) static void rist_rtcp_recv(sout_access_out_t *p_access, struct rist_flow *flow, uint8_t *pkt_raw, 
    size_t len)
{
    sout_access_out_sys_t *p_sys = p_access->p_sys;
    uint8_t *pkt = pkt_raw;
    uint8_t  ptype;
    uint16_t processed_bytes = 0;
    uint16_t records;

    while (processed_bytes < len) {
        pkt = pkt_raw + processed_bytes;
        /* safety checks */
        uint16_t bytes_left = len - processed_bytes + 1;
        if ( bytes_left < 4 )
        {
            /* we must have at least 4 bytes */
            msg_Err(p_access, "Rist rtcp packet must have at least 4 bytes, we have %d", 
                bytes_left);
            return; 
        }
        else if (!rtp_check_hdr(pkt))
        {
            /* check for a valid rtp header */
            msg_Err(p_access, "Malformed feedback packet starting with %02x, ignoring.", pkt[0]);
            return;
        }

        ptype =  rtcp_get_pt(pkt);
        records = rtcp_get_length(pkt);
        uint16_t bytes = (uint16_t)(4 * (1 + records));
        if (bytes > bytes_left)
        {
            /* check for a sane number of bytes */
            msg_Err(p_access, "Malformed feedback packet, wrong len %d, expecting %u bytes in the" \
                " packet, got a buffer of %u bytes. ptype = %d", rtcp_get_length(pkt), bytes, 
                bytes_left, ptype);
            return;
        }

        switch(ptype) {
            case RTCP_PT_RTPFR:
            case RTCP_PT_RTPFB:
                process_nack(p_access, ptype, records, flow, pkt);
                break;

            case RTCP_PT_RR:
                /*
                if (p_sys->b_ismulticast == false)
                    process_rr(f, pkt, len);
                */
                break;

            case RTCP_PT_SDES:
                {
                    if (p_sys->b_ismulticast == false)
                    {
                        int8_t name_length = rtcp_sdes_get_name_length(pkt);
                        if (name_length > bytes_left)
                        {
                            /* check for a sane number of bytes */
                            msg_Err(p_access, "Malformed SDES packet, wrong cname len %u, got a " \
                                "buffer of %u bytes.", name_length, bytes_left);
                            return;
                        }
                        if (memcmp(pkt + RTCP_SDES_SIZE, p_sys->receiver_name, name_length) != 0)
                        {
                            memcpy(p_sys->receiver_name, pkt + RTCP_SDES_SIZE, name_length);
                            msg_Info(p_access, "Receiver name: %s", p_sys->receiver_name);
                        }
                    }
                }
                break;

            case RTCP_PT_SR:
                break;

            default:
                msg_Err(p_access, "   Unrecognized RTCP packet with PTYPE=%02x!!", ptype);
        }
        processed_bytes += bytes;
    }
}