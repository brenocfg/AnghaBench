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
typedef  int /*<<< orphan*/  vlc_tls_t ;
typedef  int /*<<< orphan*/  vlc_tls_client_t ;
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int vlc_getaddrinfo_i11e (char const*,unsigned int,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_tls_ClientSessionCreate (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char const*,char const*,char const* const*,char**) ; 
 int /*<<< orphan*/  vlc_tls_SessionDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_tls_SocketOpenAddrInfo (struct addrinfo const*,int) ; 

vlc_tls_t *vlc_tls_SocketOpenTLS(vlc_tls_client_t *creds, const char *name,
                                 unsigned port, const char *service,
                                 const char *const *alpn, char **alp)
{
    struct addrinfo hints =
    {
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = IPPROTO_TCP,
    }, *res;

    msg_Dbg(creds, "resolving %s ...", name);

    int val = vlc_getaddrinfo_i11e(name, port, &hints, &res);
    if (val != 0)
    {   /* TODO: C locale for gai_strerror() */
        msg_Err(creds, "cannot resolve %s port %u: %s", name, port,
                gai_strerror(val));
        return NULL;
    }

    for (const struct addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        vlc_tls_t *tcp = vlc_tls_SocketOpenAddrInfo(p, true);
        if (tcp == NULL)
        {
            msg_Err(creds, "socket error: %s", vlc_strerror_c(errno));
            continue;
        }

        vlc_tls_t *tls = vlc_tls_ClientSessionCreate(creds, tcp, name, service,
                                                     alpn, alp);
        if (tls != NULL)
        {   /* Success! */
            freeaddrinfo(res);
            return tls;
        }

        msg_Err(creds, "connection error: %s", vlc_strerror_c(errno));
        vlc_tls_SessionDelete(tcp);
    }

    /* Failure! */
    freeaddrinfo(res);
    return NULL;
}