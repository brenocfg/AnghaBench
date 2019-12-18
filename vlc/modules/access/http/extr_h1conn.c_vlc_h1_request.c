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
struct vlc_http_stream {int dummy; } ;
struct vlc_http_msg {int dummy; } ;
struct vlc_http_conn {int dummy; } ;
struct addrinfo {struct addrinfo* ai_next; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; } ;

/* Variables and functions */
 int /*<<< orphan*/  IPPROTO_TCP ; 
 int /*<<< orphan*/  SOCK_STREAM ; 
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  freeaddrinfo (struct addrinfo*) ; 
 int /*<<< orphan*/  gai_strerror (int) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int vlc_getaddrinfo_i11e (char const*,unsigned int,struct addrinfo*,struct addrinfo**) ; 
 struct vlc_http_conn* vlc_h1_conn_create (void*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_http_conn_release (struct vlc_http_conn*) ; 
 int /*<<< orphan*/  vlc_http_dbg (void*,char*,char const*) ; 
 int /*<<< orphan*/  vlc_http_err (void*,char*,char const*,...) ; 
 struct vlc_http_stream* vlc_http_stream_open (struct vlc_http_conn*,struct vlc_http_msg const*) ; 
 int /*<<< orphan*/  vlc_strerror_c (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_tls_SessionDelete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlc_tls_SocketOpenAddrInfo (struct addrinfo const*,int) ; 

struct vlc_http_stream *vlc_h1_request(void *ctx, const char *hostname,
                                       unsigned port, bool proxy,
                                       const struct vlc_http_msg *req,
                                       bool idempotent,
                                       struct vlc_http_conn **restrict connp)
{
    struct addrinfo hints =
    {
        .ai_socktype = SOCK_STREAM,
        .ai_protocol = IPPROTO_TCP,
    }, *res;

    vlc_http_dbg(ctx, "resolving %s ...", hostname);

    int val = vlc_getaddrinfo_i11e(hostname, port, &hints, &res);
    if (val != 0)
    {   /* TODO: C locale for gai_strerror() */
        vlc_http_err(ctx, "cannot resolve %s: %s", hostname,
                     gai_strerror(val));
        return NULL;
    }

    for (const struct addrinfo *p = res; p != NULL; p = p->ai_next)
    {
        vlc_tls_t *tcp = vlc_tls_SocketOpenAddrInfo(p, idempotent);
        if (tcp == NULL)
        {
            vlc_http_err(ctx, "socket error: %s", vlc_strerror_c(errno));
            continue;
        }

        struct vlc_http_conn *conn = vlc_h1_conn_create(ctx, tcp, proxy);
        if (unlikely(conn == NULL))
        {
            vlc_tls_SessionDelete(tcp);
            continue;
        }

        /* Send the HTTP request */
        struct vlc_http_stream *stream = vlc_http_stream_open(conn, req);

        if (stream != NULL)
        {
            if (connp != NULL)
                *connp = conn;
            else
                vlc_http_conn_release(conn);

            freeaddrinfo(res);
            return stream;
        }

        vlc_http_conn_release(conn);

        if (!idempotent)
            break; /* If the request is nonidempotent, it cannot be resent. */
    }

    /* All address info failed. */
    freeaddrinfo(res);
    return NULL;
}