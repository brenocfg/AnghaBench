#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int dummy; } ;
struct TYPE_6__ {int /*<<< orphan*/  sin_port; } ;
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct TYPE_5__ {scalar_t__ sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sock_info {TYPE_3__ peer; int /*<<< orphan*/  s; TYPE_2__ addr; } ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  INVALID_SOCKET ; 
 int NUM_UDP_PEERS ; 
 int /*<<< orphan*/  SERVERIP ; 
 int /*<<< orphan*/  SERVERPORT ; 
 scalar_t__ SOCKET_ERROR ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  do_bind (int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 scalar_t__ getsockname (int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inet_addr (int /*<<< orphan*/ ) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  memcpy (char*,scalar_t__*,int) ; 
 int /*<<< orphan*/  memset (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ok (int,char*,...) ; 
 int recvfrom (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int*) ; 
 int sendto (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ,struct sockaddr*,int) ; 
 int /*<<< orphan*/  socket (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void test_UDP(void)
{
    /* This function tests UDP sendto() and recvfrom(). UDP is unreliable, so it is
       possible that this test fails due to dropped packets. */

    /* peer 0 receives data from all other peers */
    struct sock_info peer[NUM_UDP_PEERS];
    char buf[16];
    int ss, i, n_recv, n_sent;

    memset (buf,0,sizeof(buf));
    for ( i = NUM_UDP_PEERS - 1; i >= 0; i-- ) {
        ok ( ( peer[i].s = socket ( AF_INET, SOCK_DGRAM, 0 ) ) != INVALID_SOCKET, "UDP: socket failed\n" );

        peer[i].addr.sin_family         = AF_INET;
        peer[i].addr.sin_addr.s_addr    = inet_addr ( SERVERIP );

        if ( i == 0 ) {
            peer[i].addr.sin_port       = htons ( SERVERPORT );
        } else {
            peer[i].addr.sin_port       = htons ( 0 );
        }

        do_bind ( peer[i].s, (struct sockaddr *) &peer[i].addr, sizeof( peer[i].addr ) );

        /* test getsockname() to get peer's port */
        ss = sizeof ( peer[i].addr );
        ok ( getsockname ( peer[i].s, (struct sockaddr *) &peer[i].addr, &ss ) != SOCKET_ERROR, "UDP: could not getsockname()\n" );
        ok ( peer[i].addr.sin_port != htons ( 0 ), "UDP: bind() did not associate port\n" );
    }

    /* test getsockname() */
    ok ( peer[0].addr.sin_port == htons ( SERVERPORT ), "UDP: getsockname returned incorrect peer port\n" );

    for ( i = 1; i < NUM_UDP_PEERS; i++ ) {
        /* send client's ip */
        memcpy( buf, &peer[i].addr.sin_port, sizeof(peer[i].addr.sin_port) );
        n_sent = sendto ( peer[i].s, buf, sizeof(buf), 0, (struct sockaddr*) &peer[0].addr, sizeof(peer[0].addr) );
        ok ( n_sent == sizeof(buf), "UDP: sendto() sent wrong amount of data or socket error: %d\n", n_sent );
    }

    for ( i = 1; i < NUM_UDP_PEERS; i++ ) {
        n_recv = recvfrom ( peer[0].s, buf, sizeof(buf), 0,(struct sockaddr *) &peer[0].peer, &ss );
        ok ( n_recv == sizeof(buf), "UDP: recvfrom() received wrong amount of data or socket error: %d\n", n_recv );
        ok ( memcmp ( &peer[0].peer.sin_port, buf, sizeof(peer[0].addr.sin_port) ) == 0, "UDP: port numbers do not match\n" );
    }
}