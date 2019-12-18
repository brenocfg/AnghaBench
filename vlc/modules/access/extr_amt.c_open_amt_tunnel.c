#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_in {int /*<<< orphan*/  sin_addr; } ;
struct addrinfo {scalar_t__ ai_addr; struct addrinfo* ai_next; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct TYPE_21__ {TYPE_5__* p_sys; } ;
typedef  TYPE_4__ stream_t ;
typedef  int /*<<< orphan*/  hints ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_19__ {scalar_t__ s_addr; } ;
struct TYPE_20__ {TYPE_2__ sin_addr; } ;
struct TYPE_18__ {int /*<<< orphan*/  sin_addr; } ;
struct TYPE_22__ {char* relay; int tryAMT; char* relayDisco; int /*<<< orphan*/  updateTimer; TYPE_3__ mcastSrcAddr; TYPE_1__ relayDiscoAddr; } ;
typedef  TYPE_5__ access_sys_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AMT_PORT ; 
 int /*<<< orphan*/ * BlockAMT (TYPE_4__*,int*) ; 
 int INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 scalar_t__ amt_joinASM_group (TYPE_4__*) ; 
 scalar_t__ amt_joinSSM_group (TYPE_4__*) ; 
 int /*<<< orphan*/  amt_rcv_relay_adv (TYPE_4__*) ; 
 int /*<<< orphan*/  amt_rcv_relay_mem_query (TYPE_4__*) ; 
 int /*<<< orphan*/  amt_send_mem_update (TYPE_4__*,char*,int) ; 
 int /*<<< orphan*/  amt_send_relay_discovery_msg (TYPE_4__*,char*) ; 
 int /*<<< orphan*/  amt_send_relay_request (TYPE_4__*,char*) ; 
 scalar_t__ amt_sockets_init (TYPE_4__*) ; 
 int /*<<< orphan*/  block_Release (int /*<<< orphan*/ *) ; 
 int errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/ * inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memset (struct addrinfo*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  msg_Dbg (TYPE_4__*,char*,...) ; 
 int /*<<< orphan*/  msg_Err (TYPE_4__*,char*,...) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_getaddrinfo (char*,int /*<<< orphan*/ ,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  vlc_killed () ; 
 int /*<<< orphan*/  vlc_strerror (int) ; 
 int /*<<< orphan*/  vlc_timer_disarm (int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool open_amt_tunnel( stream_t *p_access )
{
    struct addrinfo hints, *serverinfo, *server;
    access_sys_t *sys = p_access->p_sys;

    memset( &hints, 0, sizeof( hints ));
    hints.ai_family = AF_INET;  /* Setting to AF_UNSPEC accepts both IPv4 and IPv6 */
    hints.ai_socktype = SOCK_DGRAM;

    msg_Dbg( p_access, "Attempting AMT to %s...", sys->relay);
    sys->tryAMT = true;

    /* Retrieve list of addresses matching the AMT relay */
    int response = vlc_getaddrinfo( sys->relay, AMT_PORT, &hints, &serverinfo );

    /* If an error returned print reason and exit */
    if( response != 0 )
    {
        msg_Err( p_access, "Could not find relay %s, reason: %s", sys->relay, gai_strerror(response) );
        goto error;
    }

    /* Iterate through the list of sockets to find one that works */
    for (server = serverinfo; server != NULL && !vlc_killed(); server = server->ai_next)
    {
        struct sockaddr_in *server_addr = (struct sockaddr_in *) server->ai_addr;
        char relay_ip[INET_ADDRSTRLEN];

        /* Convert to binary representation */
        if( unlikely( inet_ntop(AF_INET, &(server_addr->sin_addr), relay_ip, INET_ADDRSTRLEN) == NULL ) )
        {
            int errConv = errno;
            msg_Err(p_access, "Could not convert relay ip to binary representation: %s", gai_strerror(errConv));
            goto error;
        }

        /* Store string representation */
        memcpy(sys->relayDisco, relay_ip, INET_ADDRSTRLEN);
        if( unlikely( sys->relayDisco == NULL ) )
        {
            goto error;
        }

        msg_Dbg( p_access, "Trying AMT Server: %s", sys->relayDisco);

        /* Store the binary representation */
        sys->relayDiscoAddr.sin_addr = server_addr->sin_addr;

        if( amt_sockets_init( p_access ) != 0 )
            continue; /* Try next server */

        /* Negotiate with AMT relay and confirm you can pull a UDP packet  */
        amt_send_relay_discovery_msg( p_access, relay_ip );
        msg_Dbg( p_access, "Sent relay AMT discovery message to %s", relay_ip );

        if( !amt_rcv_relay_adv( p_access ) )
        {
            msg_Err( p_access, "Error receiving AMT relay advertisement msg from %s, skipping", relay_ip );
            goto error;
        }
        msg_Dbg( p_access, "Received AMT relay advertisement from %s", relay_ip );

        amt_send_relay_request( p_access, relay_ip );
        msg_Dbg( p_access, "Sent AMT relay request message to %s", relay_ip );

        if( !amt_rcv_relay_mem_query( p_access ) )
        {
            msg_Err( p_access, "Could not receive AMT relay membership query from %s, reason: %s", relay_ip, vlc_strerror(errno));
            goto error;
        }
        msg_Dbg( p_access, "Received AMT relay membership query from %s", relay_ip );

        /* If single source multicast send SSM join */
        if( sys->mcastSrcAddr.sin_addr.s_addr )
        {
            if( amt_joinSSM_group( p_access ) != 0 )
            {
                msg_Err( p_access, "Error joining SSM %s", vlc_strerror(errno) );
                goto error;
            }
            msg_Dbg( p_access, "Joined SSM" );
        }

        /* If any source multicast send ASM join */
        else {
            if( amt_joinASM_group( p_access ) != 0 )
            {
                msg_Err( p_access, "Error joining ASM %s", vlc_strerror(errno) );
                goto error;
            }
            msg_Dbg( p_access, "Joined ASM group" );
        }

        /* If started, the timer must be stopped before trying the next server
         * in order to avoid data-race with sys->sAMT. */
        vlc_timer_disarm( sys->updateTimer );

        amt_send_mem_update( p_access, sys->relayDisco, false );
        bool eof=false;
        block_t *pkt;

        /* Confirm that you can pull a UDP packet from the socket */
        if ( !(pkt = BlockAMT( p_access, &eof )) )
        {
            msg_Err( p_access, "Unable to receive UDP packet from AMT relay %s for multicast group", relay_ip );
            continue;
        }
        else
        {
            block_Release( pkt );
            msg_Dbg( p_access, "Got UDP packet from multicast group via AMT relay %s, continuing...", relay_ip );
            break;   /* found an active server sending UDP packets, so exit loop */
        }
    }

    /* if server is NULL then no AMT relay is responding */
    if (server == NULL)
    {
        msg_Err( p_access, "No AMT servers responding" );
        goto error;
    }

    /* release the allocated memory */
    freeaddrinfo( serverinfo );
    return true;

error:
    vlc_timer_disarm( sys->updateTimer );
    if( serverinfo )
        freeaddrinfo( serverinfo );
    return false;
}