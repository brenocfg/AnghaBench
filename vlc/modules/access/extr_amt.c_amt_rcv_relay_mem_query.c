#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_10__ {TYPE_4__* p_sys; } ;
typedef  TYPE_3__ stream_t ;
typedef  scalar_t__ ssize_t ;
struct TYPE_9__ {char type; char max_resp_code; scalar_t__ checksum; scalar_t__ ssmIP; char s_qrv; int qqic; scalar_t__ nSrc; } ;
struct TYPE_8__ {scalar_t__ type; scalar_t__* uchaMAC; scalar_t__ ulRcvedNonce; } ;
struct TYPE_11__ {scalar_t__ glob_ulNonce; TYPE_2__ relay_igmp_query; int /*<<< orphan*/  updateTimer; TYPE_1__ relay_mem_query_msg; int /*<<< orphan*/  sAMT; int /*<<< orphan*/  timeout; } ;
typedef  TYPE_4__ access_sys_t ;

/* Variables and functions */
 size_t AMT_HDR_LEN ; 
 size_t IP_HDR_IGMP_LEN ; 
 size_t MAC_LEN ; 
 int MSG_TYPE_LEN ; 
 size_t NONCE_LEN ; 
 int /*<<< orphan*/  POLLIN ; 
 int RELAY_QUERY_MSG_LEN ; 
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (char) ; 
 int /*<<< orphan*/  assert (int) ; 
 int /*<<< orphan*/  memcpy (scalar_t__*,char*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_3__*,char*) ; 
 int /*<<< orphan*/  msg_Warn (TYPE_3__*,char*,scalar_t__,scalar_t__) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 
 int vlc_poll_i11e (struct pollfd*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_timer_schedule (int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool amt_rcv_relay_mem_query( stream_t *p_access )
{
    char pkt[RELAY_QUERY_MSG_LEN];
    memset( pkt, 0, RELAY_QUERY_MSG_LEN );
    struct pollfd ufd[1];
    access_sys_t *sys = p_access->p_sys;

    ufd[0].fd = sys->sAMT;
    ufd[0].events = POLLIN;

    switch( vlc_poll_i11e(ufd, 1, sys->timeout) )
    {
        case 0:
            msg_Err(p_access, "AMT relay membership query receive time-out");
            /* fall through */
        case -1:
            return false;
    }

    ssize_t len = recv( sys->sAMT, pkt, RELAY_QUERY_MSG_LEN, 0 );

    if (len < 0 || len != RELAY_QUERY_MSG_LEN)
    {
        msg_Err(p_access, "length less than zero");
        return false;
    }

    memcpy( &sys->relay_mem_query_msg.type, &pkt[0], MSG_TYPE_LEN );
    /* pkt[1] is reserved  */
    memcpy( &sys->relay_mem_query_msg.uchaMAC[0], &pkt[AMT_HDR_LEN], MAC_LEN );
    memcpy( &sys->relay_mem_query_msg.ulRcvedNonce, &pkt[AMT_HDR_LEN + MAC_LEN], NONCE_LEN );
    if( sys->relay_mem_query_msg.ulRcvedNonce != sys->glob_ulNonce )
    {
        msg_Warn( p_access, "Nonces are different rcvd: %x glob: %x", sys->relay_mem_query_msg.ulRcvedNonce, sys->glob_ulNonce );
        return false;
    }

    size_t shift = AMT_HDR_LEN + MAC_LEN + NONCE_LEN + IP_HDR_IGMP_LEN;
    sys->relay_igmp_query.type = pkt[shift];
    shift++; assert( shift < RELAY_QUERY_MSG_LEN);
    sys->relay_igmp_query.max_resp_code = pkt[shift];
    shift++; assert( shift < RELAY_QUERY_MSG_LEN);
    memcpy( &sys->relay_igmp_query.checksum, &pkt[shift], 2 );
    shift += 2; assert( shift < RELAY_QUERY_MSG_LEN);
    memcpy( &sys->relay_igmp_query.ssmIP, &pkt[shift], 4 );
    shift += 4; assert( shift < RELAY_QUERY_MSG_LEN);
    sys->relay_igmp_query.s_qrv = pkt[shift];
    shift++; assert( shift < RELAY_QUERY_MSG_LEN);
    if( pkt[shift] == 0 )
        sys->relay_igmp_query.qqic = 125;
    else
        sys->relay_igmp_query.qqic = pkt[shift];

    shift++; assert( shift < RELAY_QUERY_MSG_LEN);
    memcpy( &sys->relay_igmp_query.nSrc, &pkt[shift], 2 );

    /* Arms the timer for a single shot: cf. amt_update_timer_cb comment */
    vlc_timer_schedule( sys->updateTimer, false,
                        VLC_TICK_FROM_SEC( sys->relay_igmp_query.qqic ), 0 );

    return true;
}