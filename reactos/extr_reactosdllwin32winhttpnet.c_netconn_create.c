#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct sockaddr_storage {int ss_family; } ;
struct sockaddr_in6 {int dummy; } ;
struct sockaddr_in {int dummy; } ;
struct sockaddr {int dummy; } ;
struct pollfd {int fd; int /*<<< orphan*/  events; } ;
struct TYPE_6__ {int socket; struct sockaddr_storage sockaddr; int /*<<< orphan*/ * host; } ;
typedef  TYPE_1__ netconn_t ;
typedef  int /*<<< orphan*/  hostdata_t ;
typedef  int ULONG ;
typedef  int /*<<< orphan*/  BOOL ;

/* Variables and functions */
#define  AF_INET 129 
#define  AF_INET6 128 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  FIONBIO ; 
 int /*<<< orphan*/  POLLOUT ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  WARN (char*,int) ; 
 int WSAEINPROGRESS ; 
 int WSAEINTR ; 
 int WSAEWOULDBLOCK ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 scalar_t__ connect (int,struct sockaddr const*,unsigned int) ; 
 int /*<<< orphan*/  errno ; 
 TYPE_1__* heap_alloc_zero (int) ; 
 int /*<<< orphan*/  heap_free (TYPE_1__*) ; 
 int /*<<< orphan*/  ioctlsocket (int,int /*<<< orphan*/ ,int*) ; 
 int /*<<< orphan*/  netconn_close (TYPE_1__*) ; 
 scalar_t__ poll (struct pollfd*,int,int) ; 
 int /*<<< orphan*/  set_last_error (int) ; 
 int sock_get_error (int /*<<< orphan*/ ) ; 
 int socket (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int strerror (int /*<<< orphan*/ ) ; 

netconn_t *netconn_create( hostdata_t *host, const struct sockaddr_storage *sockaddr, int timeout )
{
    netconn_t *conn;
    unsigned int addr_len;
    BOOL ret = FALSE;
    int res;
    ULONG state;

    conn = heap_alloc_zero(sizeof(*conn));
    if (!conn) return NULL;
    conn->host = host;
    conn->sockaddr = *sockaddr;
    if ((conn->socket = socket( sockaddr->ss_family, SOCK_STREAM, 0 )) == -1)
    {
        WARN("unable to create socket (%s)\n", strerror(errno));
        set_last_error( sock_get_error( errno ) );
        heap_free(conn);
        return NULL;
    }

    switch (conn->sockaddr.ss_family)
    {
    case AF_INET:
        addr_len = sizeof(struct sockaddr_in);
        break;
    case AF_INET6:
        addr_len = sizeof(struct sockaddr_in6);
        break;
    default:
        assert(0);
    }

    if (timeout > 0)
    {
        state = 1;
        ioctlsocket( conn->socket, FIONBIO, &state );
    }

    for (;;)
    {
        res = 0;
        if (connect( conn->socket, (const struct sockaddr *)&conn->sockaddr, addr_len ) < 0)
        {
            res = sock_get_error( errno );
            if (res == WSAEWOULDBLOCK || res == WSAEINPROGRESS)
            {
#ifdef __REACTOS__
                /* ReactOS: use select instead of poll */
                fd_set outfd;
                struct timeval tv;

                FD_ZERO(&outfd);
                FD_SET(conn->socket, &outfd);

                tv.tv_sec = 0;
                tv.tv_usec = timeout * 1000;
                for (;;)
                {
                    res = 0;

                    if (select( 0, NULL, &outfd, NULL, &tv ) > 0)
#else
                struct pollfd pfd;

                pfd.fd = conn->socket;
                pfd.events = POLLOUT;
                for (;;)
                {
                    res = 0;
                    if (poll( &pfd, 1, timeout ) > 0)
#endif
                    {
                        ret = TRUE;
                        break;
                    }
                    else
                    {
                        res = sock_get_error( errno );
                        if (res != WSAEINTR) break;
                    }
                }
            }
            if (res != WSAEINTR) break;
        }
        else
        {
            ret = TRUE;
            break;
        }
    }
    if (timeout > 0)
    {
        state = 0;
        ioctlsocket( conn->socket, FIONBIO, &state );
    }
    if (!ret)
    {
        WARN("unable to connect to host (%d)\n", res);
        set_last_error( res );
        netconn_close( conn );
        return NULL;
    }
    return conn;
}