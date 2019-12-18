#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
struct addrinfo {scalar_t__ ai_socktype; int ai_protocol; int ai_flags; scalar_t__ ai_family; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int AI_IDN ; 
 int AI_NUMERICSERV ; 
 int AI_PASSIVE ; 
 scalar_t__ SOCK_DGRAM ; 
 scalar_t__ connect (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,unsigned int,char const*,unsigned int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int net_ListenSingle (int /*<<< orphan*/ *,char const*,unsigned int,int) ; 
 int net_SetupDgramSocket (int /*<<< orphan*/ *,int,struct addrinfo*) ; 
 scalar_t__ net_SockAddrIsMulticast (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int net_Socket (int /*<<< orphan*/ *,scalar_t__,scalar_t__,int) ; 
 scalar_t__ net_SourceSubscribe (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  net_errno ; 
 int vlc_getaddrinfo (char const*,unsigned int,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 

int net_OpenDgram( vlc_object_t *obj, const char *psz_bind, unsigned i_bind,
                   const char *psz_server, unsigned i_server, int protocol )
{
    if ((psz_server == NULL) || (psz_server[0] == '\0'))
        return net_ListenSingle (obj, psz_bind, i_bind, protocol);

    msg_Dbg (obj, "net: connecting to [%s]:%u from [%s]:%u",
             psz_server, i_server, psz_bind, i_bind);

    struct addrinfo hints = {
        .ai_socktype = SOCK_DGRAM,
        .ai_protocol = protocol,
        .ai_flags = AI_NUMERICSERV | AI_IDN,
    }, *loc, *rem;

    int val = vlc_getaddrinfo (psz_server, i_server, &hints, &rem);
    if (val)
    {
        msg_Err (obj, "cannot resolve %s port %u : %s", psz_server, i_server,
                 gai_strerror (val));
        return -1;
    }

    hints.ai_flags |= AI_PASSIVE;
    val = vlc_getaddrinfo (psz_bind, i_bind, &hints, &loc);
    if (val)
    {
        msg_Err (obj, "cannot resolve %s port %u : %s", psz_bind, i_bind,
                 gai_strerror (val));
        freeaddrinfo (rem);
        return -1;
    }

    val = -1;
    for (struct addrinfo *ptr = loc; ptr != NULL; ptr = ptr->ai_next)
    {
        int fd = net_Socket (obj, ptr->ai_family, ptr->ai_socktype,
                             ptr->ai_protocol);
        if (fd == -1)
            continue; // usually, address family not supported

        fd = net_SetupDgramSocket( obj, fd, ptr );
        if( fd == -1 )
            continue;

        for (struct addrinfo *ptr2 = rem; ptr2 != NULL; ptr2 = ptr2->ai_next)
        {
            if ((ptr2->ai_family != ptr->ai_family)
             || (ptr2->ai_socktype != ptr->ai_socktype)
             || (ptr2->ai_protocol != ptr->ai_protocol))
                continue;

            if (net_SockAddrIsMulticast (ptr->ai_addr, ptr->ai_addrlen)
              ? net_SourceSubscribe (obj, fd,
                                     ptr2->ai_addr, ptr2->ai_addrlen,
                                     ptr->ai_addr, ptr->ai_addrlen)
              : connect (fd, ptr2->ai_addr, ptr2->ai_addrlen))
            {
                msg_Err (obj, "cannot connect to %s port %u: %s",
                         psz_server, i_server, vlc_strerror_c(net_errno));
                continue;
            }
            val = fd;
            break;
        }

        if (val != -1)
            break;

        net_Close (fd);
    }

    freeaddrinfo (rem);
    freeaddrinfo (loc);
    return val;
}