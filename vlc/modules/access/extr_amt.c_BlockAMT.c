#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct pollfd {int /*<<< orphan*/  events; int /*<<< orphan*/  fd; } ;
struct TYPE_10__ {TYPE_3__* p_sys; } ;
typedef  TYPE_1__ stream_t ;
typedef  scalar_t__ ssize_t ;
typedef  int socklen_t ;
struct TYPE_11__ {scalar_t__* p_buffer; int /*<<< orphan*/  i_buffer; int /*<<< orphan*/  i_flags; } ;
typedef  TYPE_2__ block_t ;
struct TYPE_12__ {scalar_t__ mtu; int /*<<< orphan*/  sAMT; scalar_t__ tryAMT; int /*<<< orphan*/  timeout; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 scalar_t__ AMT_HDR_LEN ; 
 scalar_t__ AMT_MULT_DATA ; 
 int /*<<< orphan*/  BLOCK_FLAG_CORRUPTED ; 
 scalar_t__ IP_HDR_LEN ; 
 int /*<<< orphan*/  POLLIN ; 
 scalar_t__ UDP_HDR_LEN ; 
 TYPE_2__* block_Alloc (scalar_t__) ; 
 int /*<<< orphan*/  block_Release (TYPE_2__*) ; 
 int /*<<< orphan*/  msg_Err (TYPE_1__*,char*,...) ; 
 int /*<<< orphan*/  open_amt_tunnel (TYPE_1__*) ; 
 scalar_t__ recv (int /*<<< orphan*/ ,scalar_t__*,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ recvfrom (int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_poll_i11e (struct pollfd*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static block_t *BlockAMT(stream_t *p_access, bool *restrict eof)
{
    access_sys_t *sys = p_access->p_sys;
    ssize_t len = 0, shift = 0, tunnel = IP_HDR_LEN + UDP_HDR_LEN + AMT_HDR_LEN;

    /* Allocate anticipated MTU buffer for holding the UDP packet suitable for native or AMT tunneled multicast */
    block_t *pkt = block_Alloc( sys->mtu + tunnel );
    if ( unlikely( pkt == NULL ) )
        return NULL;

    struct pollfd ufd[1];

    if( sys->tryAMT )
        ufd[0].fd = sys->sAMT; /* AMT tunneling file descriptor */
    else
        ufd[0].fd = sys->fd;   /* Native multicast file descriptor */
    ufd[0].events = POLLIN;

    switch (vlc_poll_i11e(ufd, 1, sys->timeout))
    {
        case 0:
            if( !sys->tryAMT )
            {
                msg_Err(p_access, "Native multicast receive time-out");
                if( !open_amt_tunnel( p_access ) )
                    goto error;
                break;
            }
            else
            {
                *eof = true;
            }
            /* fall through */
        case -1:
            goto error;
    }

    /* If using AMT tunneling perform basic checks and point to beginning of the payload */
    if( sys->tryAMT )
    {
        /* AMT is a wrapper for UDP streams, so recv is used. */
        len = recv( sys->sAMT, pkt->p_buffer, sys->mtu + tunnel, 0 );

        /* Check for the integrity of the received AMT packet */
        if( len < 0 || *(pkt->p_buffer) != AMT_MULT_DATA )
            goto error;

        /* Set the offet to the first byte of the payload */
        shift += tunnel;

        /* If the length received is less than the AMT tunnel header then it's truncated */
        if( len < tunnel )
        {
            msg_Err(p_access, "%zd bytes packet truncated (MTU was %zd)", len, sys->mtu);
            pkt->i_flags |= BLOCK_FLAG_CORRUPTED;
        }

        /* Otherwise subtract the length of the AMT encapsulation from the packet received */
        else
        {
            len -= tunnel;
        }
    }
    /* Otherwise pull native multicast */
    else
    {
        struct sockaddr temp;
        socklen_t temp_size = sizeof( struct sockaddr );
        len = recvfrom( sys->sAMT, (char *)pkt->p_buffer, sys->mtu + tunnel, 0, (struct sockaddr*)&temp, &temp_size );
    }

    /* Set the offset to payload start */
    pkt->p_buffer += shift;
    pkt->i_buffer -= shift;

    return pkt;

error:
    block_Release( pkt );
    return NULL;
}