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
struct addrinfo {int ai_socktype; int ai_protocol; int ai_flags; int /*<<< orphan*/  ai_addrlen; int /*<<< orphan*/  ai_addr; int /*<<< orphan*/  ai_family; struct addrinfo* ai_next; } ;

/* Variables and functions */
 int AI_IDN ; 
 int AI_NUMERICSERV ; 
 int AI_PASSIVE ; 
 int /*<<< orphan*/  INT_MAX ; 
 scalar_t__ bind (int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 scalar_t__ listen (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  net_Close (int) ; 
 int net_Socket (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int net_errno ; 
 scalar_t__ realloc (int*,unsigned int) ; 
 int rootwrap_bind (int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int vlc_getaddrinfo (char const*,unsigned int,struct addrinfo*,struct addrinfo**) ; 
 int vlc_strerror_c (int) ; 

int *net_Listen (vlc_object_t *p_this, const char *psz_host,
                 unsigned i_port, int type, int protocol)
{
    struct addrinfo hints = {
        .ai_socktype = type,
        .ai_protocol = protocol,
        .ai_flags = AI_PASSIVE | AI_NUMERICSERV | AI_IDN,
    }, *res;

    msg_Dbg (p_this, "net: listening to %s port %u",
             (psz_host != NULL) ? psz_host : "*", i_port);

    int i_val = vlc_getaddrinfo (psz_host, i_port, &hints, &res);
    if (i_val)
    {
        msg_Err (p_this, "Cannot resolve %s port %u : %s",
                 (psz_host != NULL) ? psz_host : "", i_port,
                 gai_strerror (i_val));
        return NULL;
    }

    int *sockv = NULL;
    unsigned sockc = 0;

    for (struct addrinfo *ptr = res; ptr != NULL; ptr = ptr->ai_next)
    {
        int fd = net_Socket (p_this, ptr->ai_family, ptr->ai_socktype,
                             ptr->ai_protocol);
        if (fd == -1)
        {
            msg_Dbg (p_this, "socket error: %s", vlc_strerror_c(net_errno));
            continue;
        }

        /* Bind the socket */
        if (bind (fd, ptr->ai_addr, ptr->ai_addrlen))
        {
            int err = net_errno;
            net_Close (fd);
#if !defined(_WIN32)
            fd = rootwrap_bind (ptr->ai_family, ptr->ai_socktype,
                                ptr->ai_protocol,
                                ptr->ai_addr, ptr->ai_addrlen);
            if (fd != -1)
            {
                msg_Dbg (p_this, "got socket %d from rootwrap", fd);
            }
            else
#endif
            {
                msg_Err (p_this, "socket bind error: %s", vlc_strerror_c(err));
                continue;
            }
        }

        /* Listen */
        if (listen(fd, INT_MAX))
        {
            msg_Err(p_this, "socket listen error: %s",
                    vlc_strerror_c(net_errno));
            net_Close(fd);
            continue;
        }

        int *nsockv = (int *)realloc (sockv, (sockc + 2) * sizeof (int));
        if (nsockv != NULL)
        {
            nsockv[sockc++] = fd;
            sockv = nsockv;
        }
        else
            net_Close (fd);
    }

    freeaddrinfo (res);

    if (sockv != NULL)
        sockv[sockc] = -1;

    return sockv;
}