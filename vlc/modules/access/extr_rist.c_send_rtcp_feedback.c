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
typedef  int /*<<< orphan*/  uint8_t ;
struct sockaddr {int dummy; } ;
struct rist_flow {int /*<<< orphan*/  peer_socklen; int /*<<< orphan*/  peer_sockaddr; int /*<<< orphan*/  fd_nack; int /*<<< orphan*/  cname; } ;
struct TYPE_4__ {TYPE_2__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
struct TYPE_5__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ stream_sys_t ;

/* Variables and functions */
 int RTCP_EMPTY_RR_SIZE ; 
 int RTCP_SDES_SIZE ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * malloc (int) ; 
 int /*<<< orphan*/  rist_WriteTo_i11e_Locked (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,struct sockaddr*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcp_fb_set_int_ssrc_pkt_sender (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtcp_rr_set_pt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtcp_sdes_set_cname (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtcp_sdes_set_name_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtcp_sdes_set_pt (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  rtcp_set_length (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtp_set_cc (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  rtp_set_hdr (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlcpy (char*,int /*<<< orphan*/ ,int) ; 
 int strlen (int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void send_rtcp_feedback(stream_t *p_access, struct rist_flow *flow)
{
    stream_sys_t *p_sys = p_access->p_sys;
    int namelen = strlen(flow->cname) + 1;

    /* we need to make sure it is a multiple of 4, pad if necessary */
    if ((namelen - 2) & 0x3)
        namelen = ((((namelen - 2) >> 2) + 1) << 2) + 2;

    int rtcp_feedback_size = RTCP_EMPTY_RR_SIZE + RTCP_SDES_SIZE + namelen;
    uint8_t *buf = malloc(rtcp_feedback_size);
    if ( unlikely( buf == NULL ) )
        return;

    /* Populate RR */
    uint8_t *rr = buf;
    rtp_set_hdr(rr);
    rtcp_rr_set_pt(rr);
    rtcp_set_length(rr, 1);
    rtcp_fb_set_int_ssrc_pkt_sender(rr, 0);

    /* Populate SDES */
    uint8_t *p_sdes = (buf + RTCP_EMPTY_RR_SIZE);
    rtp_set_hdr(p_sdes);
    rtp_set_cc(p_sdes, 1); /* Actually it is source count in this case */
    rtcp_sdes_set_pt(p_sdes);
    rtcp_set_length(p_sdes, (namelen >> 2) + 2);
    rtcp_sdes_set_cname(p_sdes, 1);
    rtcp_sdes_set_name_length(p_sdes, strlen(flow->cname));
    uint8_t *p_sdes_name = (buf + RTCP_EMPTY_RR_SIZE + RTCP_SDES_SIZE);
    strlcpy((char *)p_sdes_name, flow->cname, namelen);

    /* Write to Socket */
    rist_WriteTo_i11e_Locked(p_sys->lock, flow->fd_nack, buf, rtcp_feedback_size,
        (struct sockaddr *)&flow->peer_sockaddr, flow->peer_socklen);
    free(buf);
    buf = NULL;
}