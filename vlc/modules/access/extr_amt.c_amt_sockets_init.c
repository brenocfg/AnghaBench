#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {void* sin_family; void* sin_port; TYPE_5__ sin_addr; } ;
struct sockaddr {int dummy; } ;
struct TYPE_8__ {TYPE_3__* p_sys; } ;
typedef  TYPE_2__ stream_t ;
typedef  int /*<<< orphan*/  rcvAddr ;
typedef  int /*<<< orphan*/  enable ;
struct TYPE_7__ {void* sin_port; void* sin_family; } ;
struct TYPE_9__ {int sAMT; int sQuery; TYPE_1__ relayDiscoAddr; } ;
typedef  TYPE_3__ access_sys_t ;

/* Variables and functions */
 void* AF_INET ; 
 int AMT_PORT ; 
 int /*<<< orphan*/  INADDR_ANY ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  LOCAL_LOOPBACK ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_REUSEADDR ; 
 scalar_t__ bind (int,struct sockaddr*,int) ; 
 int /*<<< orphan*/  errno ; 
 void* htons (int) ; 
 int inet_pton (void*,int /*<<< orphan*/ ,TYPE_5__*) ; 
 int /*<<< orphan*/  memset (struct sockaddr_in*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Err (TYPE_2__*,char*,...) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int setsockopt (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int*,int) ; 
 void* vlc_socket (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  vlc_strerror (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int amt_sockets_init( stream_t *p_access )
{
    struct sockaddr_in rcvAddr;
    access_sys_t *sys = p_access->p_sys;
    memset( &rcvAddr, 0, sizeof(struct sockaddr_in) );
    int enable = 0, res = 0;

    /* Relay anycast address for discovery */
    sys->relayDiscoAddr.sin_family = AF_INET;
    sys->relayDiscoAddr.sin_port = htons( AMT_PORT );

    /* create UDP socket */
    sys->sAMT = vlc_socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP, true );
    if( sys->sAMT == -1 )
    {
        msg_Err( p_access, "Failed to create UDP socket" );
        goto error;
    }

    res = setsockopt(sys->sAMT, SOL_SOCKET, SO_REUSEADDR, &enable, sizeof(enable));
    if(res < 0)
    {
        msg_Err( p_access, "Couldn't make socket reusable");
        goto error;
    }

    rcvAddr.sin_family      = AF_INET;
    rcvAddr.sin_port        = htons( 0 );
    rcvAddr.sin_addr.s_addr = INADDR_ANY;

    if( bind(sys->sAMT, (struct sockaddr *)&rcvAddr, sizeof(rcvAddr) ) != 0 )
    {
        msg_Err( p_access, "Failed to bind UDP socket error: %s", vlc_strerror(errno) );
        goto error;
    }

    sys->sQuery = vlc_socket( AF_INET, SOCK_DGRAM, IPPROTO_UDP, true );
    if( sys->sQuery == -1 )
    {
        msg_Err( p_access, "Failed to create query socket" );
        goto error;
    }

    /* bind socket to local address */
    struct sockaddr_in stLocalAddr = 
    {
        .sin_family      = AF_INET,
        .sin_port        = htons( 0 ),
        .sin_addr.s_addr = INADDR_ANY,
    };

    if( bind(sys->sQuery, (struct sockaddr *)&stLocalAddr, sizeof(struct sockaddr) ) != 0 )
    {
        msg_Err( p_access, "Failed to bind query socket" );
        goto error;
    }

    struct sockaddr_in stSvrAddr =
    {
        .sin_family = AF_INET,
        .sin_port = htons( 9124 ),
    };

    res = inet_pton( AF_INET, LOCAL_LOOPBACK, &stSvrAddr.sin_addr );
    if( res != 1 )
    {
        msg_Err( p_access, "Could not convert loopback address" );
        goto error;
    }
    /* TODO: stSvrAddr is unused ? */

    return 0;

error:
    if( sys->sAMT != -1 )
    {
        net_Close( sys->sAMT );
        sys->sAMT = -1;
    }

    if( sys->sQuery != -1 )
    {
        net_Close( sys->sQuery );
        sys->sQuery = -1;
    }
    return -1;
}