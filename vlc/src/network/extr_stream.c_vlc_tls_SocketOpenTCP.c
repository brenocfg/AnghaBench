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
typedef  int /*<<< orphan*/  vlc_object_t ;
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  assert (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,char const*,...) ; 
 int vlc_getaddrinfo_i11e (char const*,unsigned int,struct addrinfo*,struct addrinfo**) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlc_tls_SocketOpenAddrInfo (struct addrinfo const*,int) ; 

vlc_tls_t *vlc_tls_SocketOpenTCP(vlc_object_t *obj, const char *name,
                                 unsigned port)
{
    struct addrinfo hints =
    {
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = IPPROTO_TCP,
    }, *res;

    assert(name != NULL);
    msg_Dbg(obj, "resolving %s ...", name);

    int val = vlc_getaddrinfo_i11e(name, port, &hints, &res);
    if (val != 0)
    {   /* TODO: C locale for gai_strerror() */
        msg_Err(obj, "cannot resolve %s port %u: %s", name, port,
                gai_strerror(val));
        return NULL;
    }

    msg_Dbg(obj, "connecting to %s port %u ...", name, port);

    /* TODO: implement RFC8305 */
    for (const struct addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        vlc_tls_t *tls = vlc_tls_SocketOpenAddrInfo(p, false);
        if (tls == NULL)
        {
            msg_Err(obj, "connection error: %s", vlc_strerror_c(errno));
            continue;
        }

        freeaddrinfo(res);
        return tls;
    }

    freeaddrinfo(res);
    return NULL;
}