#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int uint16_t ;
struct sockaddr_storage {int dummy; } ;
struct sockaddr_in6 {int sin6_port; scalar_t__ sin6_scope_id; scalar_t__ sin6_flowinfo; int /*<<< orphan*/  sin6_addr; scalar_t__ sin6_family; } ;
struct sockaddr_in {int sin_port; int /*<<< orphan*/  sin_addr; scalar_t__ sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_14__ {int* s6_addr; } ;
struct ipv6_mreq {scalar_t__ ipv6mr_interface; TYPE_3__ ipv6mr_multiaddr; } ;
typedef  int /*<<< orphan*/  n ;
typedef  int /*<<< orphan*/  mreq ;
typedef  int /*<<< orphan*/  broadcast ;
struct TYPE_13__ {int /*<<< orphan*/  in6_addr; } ;
struct TYPE_12__ {int /*<<< orphan*/  in_addr; } ;
struct TYPE_16__ {scalar_t__ family; TYPE_2__ ip6; TYPE_1__ ip4; } ;
struct TYPE_15__ {scalar_t__ family; int port; int /*<<< orphan*/  sock; } ;
typedef  TYPE_4__ Networking_Core ;
typedef  TYPE_5__ IP ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 int /*<<< orphan*/  IPPROTO_IPV6 ; 
 int /*<<< orphan*/  IPPROTO_UDP ; 
 int /*<<< orphan*/  IPV6_ADD_MEMBERSHIP ; 
 int /*<<< orphan*/  LOGGER_DEBUG (char*,char*,...) ; 
 int /*<<< orphan*/  LOGGER_ERROR (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  SOCK_DGRAM ; 
 int /*<<< orphan*/  SOL_SOCKET ; 
 int /*<<< orphan*/  SO_BROADCAST ; 
 int /*<<< orphan*/  SO_RCVBUF ; 
 int /*<<< orphan*/  SO_SNDBUF ; 
 int TOX_PORTRANGE_FROM ; 
 int TOX_PORTRANGE_TO ; 
 int bind (int /*<<< orphan*/ ,struct sockaddr*,size_t) ; 
 TYPE_4__* calloc (int,int) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  free (TYPE_4__*) ; 
 int htons (int) ; 
 int /*<<< orphan*/  ip_ntoa (TYPE_5__*) ; 
 scalar_t__ is_dualstack ; 
 int /*<<< orphan*/  kill_networking (TYPE_4__*) ; 
 int /*<<< orphan*/  memset (struct ipv6_mreq*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ networking_at_startup () ; 
 int /*<<< orphan*/  ntohs (int) ; 
 scalar_t__ res ; 
 int /*<<< orphan*/  set_socket_dualstack (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_socket_nonblock (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  set_socket_nosigpipe (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  setsockopt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  sock_valid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  socket (scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 

Networking_Core *new_networking_ex(IP ip, uint16_t port_from, uint16_t port_to, unsigned int *error)
{
    /* If both from and to are 0, use default port range
     * If one is 0 and the other is non-0, use the non-0 value as only port
     * If from > to, swap
     */
    if (port_from == 0 && port_to == 0) {
        port_from = TOX_PORTRANGE_FROM;
        port_to = TOX_PORTRANGE_TO;
    } else if (port_from == 0 && port_to != 0) {
        port_from = port_to;
    } else if (port_from != 0 && port_to == 0) {
        port_to = port_from;
    } else if (port_from > port_to) {
        uint16_t temp = port_from;
        port_from = port_to;
        port_to = temp;
    }

    if (error)
        *error = 2;

    /* maybe check for invalid IPs like 224+.x.y.z? if there is any IP set ever */
    if (ip.family != AF_INET && ip.family != AF_INET6) {
#ifdef DEBUG
        fprintf(stderr, "Invalid address family: %u\n", ip.family);
#endif
        return NULL;
    }

    if (networking_at_startup() != 0)
        return NULL;

    Networking_Core *temp = calloc(1, sizeof(Networking_Core));

    if (temp == NULL)
        return NULL;

    temp->family = ip.family;
    temp->port = 0;

    /* Initialize our socket. */
    /* add log message what we're creating */
    temp->sock = socket(temp->family, SOCK_DGRAM, IPPROTO_UDP);

    /* Check for socket error. */
    if (!sock_valid(temp->sock)) {
#ifdef DEBUG
        fprintf(stderr, "Failed to get a socket?! %u, %s\n", errno, strerror(errno));
#endif
        free(temp);

        if (error)
            *error = 1;

        return NULL;
    }

    /* Functions to increase the size of the send and receive UDP buffers.
     */
    int n = 1024 * 1024 * 2;
    setsockopt(temp->sock, SOL_SOCKET, SO_RCVBUF, (char *)&n, sizeof(n));
    setsockopt(temp->sock, SOL_SOCKET, SO_SNDBUF, (char *)&n, sizeof(n));

    /* Enable broadcast on socket */
    int broadcast = 1;
    setsockopt(temp->sock, SOL_SOCKET, SO_BROADCAST, (char *)&broadcast, sizeof(broadcast));

    /* iOS UDP sockets are weird and apparently can SIGPIPE */
    if (!set_socket_nosigpipe(temp->sock)) {
        kill_networking(temp);

        if (error)
            *error = 1;

        return NULL;
    }

    /* Set socket nonblocking. */
    if (!set_socket_nonblock(temp->sock)) {
        kill_networking(temp);

        if (error)
            *error = 1;

        return NULL;
    }

    /* Bind our socket to port PORT and the given IP address (usually 0.0.0.0 or ::) */
    uint16_t *portptr = NULL;
    struct sockaddr_storage addr;
    size_t addrsize;

    if (temp->family == AF_INET) {
        struct sockaddr_in *addr4 = (struct sockaddr_in *)&addr;

        addrsize = sizeof(struct sockaddr_in);
        addr4->sin_family = AF_INET;
        addr4->sin_port = 0;
        addr4->sin_addr = ip.ip4.in_addr;

        portptr = &addr4->sin_port;
    } else if (temp->family == AF_INET6) {
        struct sockaddr_in6 *addr6 = (struct sockaddr_in6 *)&addr;

        addrsize = sizeof(struct sockaddr_in6);
        addr6->sin6_family = AF_INET6;
        addr6->sin6_port = 0;
        addr6->sin6_addr = ip.ip6.in6_addr;

        addr6->sin6_flowinfo = 0;
        addr6->sin6_scope_id = 0;

        portptr = &addr6->sin6_port;
    } else {
        free(temp);
        return NULL;
    }

    if (ip.family == AF_INET6) {
#ifdef TOX_LOGGER
        int is_dualstack =
#endif /* TOX_LOGGER */
            set_socket_dualstack(temp->sock);
        LOGGER_DEBUG( "Dual-stack socket: %s",
                      is_dualstack ? "enabled" : "Failed to enable, won't be able to receive from/send to IPv4 addresses" );
        /* multicast local nodes */
        struct ipv6_mreq mreq;
        memset(&mreq, 0, sizeof(mreq));
        mreq.ipv6mr_multiaddr.s6_addr[ 0] = 0xFF;
        mreq.ipv6mr_multiaddr.s6_addr[ 1] = 0x02;
        mreq.ipv6mr_multiaddr.s6_addr[15] = 0x01;
        mreq.ipv6mr_interface = 0;
#ifdef TOX_LOGGER
        int res =
#endif /* TOX_LOGGER */
            setsockopt(temp->sock, IPPROTO_IPV6, IPV6_ADD_MEMBERSHIP, (char *)&mreq, sizeof(mreq));

        LOGGER_DEBUG(res < 0 ? "Failed to activate local multicast membership. (%u, %s)" :
                     "Local multicast group FF02::1 joined successfully", errno, strerror(errno) );
    }

    /* a hanging program or a different user might block the standard port;
     * as long as it isn't a parameter coming from the commandline,
     * try a few ports after it, to see if we can find a "free" one
     *
     * if we go on without binding, the first sendto() automatically binds to
     * a free port chosen by the system (i.e. anything from 1024 to 65535)
     *
     * returning NULL after bind fails has both advantages and disadvantages:
     * advantage:
     *   we can rely on getting the port in the range 33445..33450, which
     *   enables us to tell joe user to open their firewall to a small range
     *
     * disadvantage:
     *   some clients might not test return of tox_new(), blindly assuming that
     *   it worked ok (which it did previously without a successful bind)
     */
    uint16_t port_to_try = port_from;
    *portptr = htons(port_to_try);
    int tries;

    for (tries = port_from; tries <= port_to; tries++) {
        int res = bind(temp->sock, (struct sockaddr *)&addr, addrsize);

        if (!res) {
            temp->port = *portptr;

            LOGGER_DEBUG("Bound successfully to %s:%u", ip_ntoa(&ip), ntohs(temp->port));

            /* errno isn't reset on success, only set on failure, the failed
             * binds with parallel clients yield a -EPERM to the outside if
             * errno isn't cleared here */
            if (tries > 0)
                errno = 0;

            if (error)
                *error = 0;

            return temp;
        }

        port_to_try++;

        if (port_to_try > port_to)
            port_to_try = port_from;

        *portptr = htons(port_to_try);
    }

    LOGGER_ERROR("Failed to bind socket: %u, %s IP: %s port_from: %u port_to: %u", errno, strerror(errno),
                 ip_ntoa(&ip), port_from, port_to);

    kill_networking(temp);

    if (error)
        *error = 1;

    return NULL;
}