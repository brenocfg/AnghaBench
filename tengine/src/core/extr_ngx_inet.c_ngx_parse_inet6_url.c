#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_9__ ;
typedef  struct TYPE_15__   TYPE_6__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  char u_char ;
struct TYPE_16__ {int /*<<< orphan*/  s6_addr; } ;
struct sockaddr_in6 {TYPE_9__ sin6_addr; void* sin6_port; void* sin6_family; } ;
struct TYPE_14__ {int /*<<< orphan*/  sockaddr; } ;
struct TYPE_13__ {size_t len; char* data; } ;
struct TYPE_12__ {int len; char* data; } ;
struct TYPE_11__ {int len; char* data; } ;
struct TYPE_10__ {char* data; size_t len; } ;
struct TYPE_15__ {int socklen; char* err; int last_port; void* port; int no_port; void* default_port; int wildcard; TYPE_5__ sockaddr; void* family; TYPE_4__ host; TYPE_3__ port_text; scalar_t__ listen; TYPE_2__ uri; int /*<<< orphan*/  uri_part; TYPE_1__ url; } ;
typedef  TYPE_6__ ngx_url_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int ngx_int_t ;
typedef  void* in_port_t ;

/* Variables and functions */
 void* AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_UNSPECIFIED (TYPE_9__*) ; 
 int NGX_ERROR ; 
 scalar_t__ NGX_OK ; 
 void* htons (void*) ; 
 int ngx_atoi (char*,size_t) ; 
 scalar_t__ ngx_inet6_addr (char*,size_t,int /*<<< orphan*/ ) ; 
 int ngx_inet_add_addr (int /*<<< orphan*/ *,TYPE_6__*,int /*<<< orphan*/ *,int,int) ; 
 char* ngx_strlchr (char*,char*,char) ; 

__attribute__((used)) static ngx_int_t
ngx_parse_inet6_url(ngx_pool_t *pool, ngx_url_t *u)
{
#if (NGX_HAVE_INET6)
    u_char               *p, *host, *port, *last, *uri, *dash;
    size_t                len;
    ngx_int_t             n;
    struct sockaddr_in6  *sin6;

    u->socklen = sizeof(struct sockaddr_in6);
    sin6 = (struct sockaddr_in6 *) &u->sockaddr;
    sin6->sin6_family = AF_INET6;

    host = u->url.data + 1;

    last = u->url.data + u->url.len;

    p = ngx_strlchr(host, last, ']');

    if (p == NULL) {
        u->err = "invalid host";
        return NGX_ERROR;
    }

    port = p + 1;

    uri = ngx_strlchr(port, last, '/');

    if (uri) {
        if (u->listen || !u->uri_part) {
            u->err = "invalid host";
            return NGX_ERROR;
        }

        u->uri.len = last - uri;
        u->uri.data = uri;

        last = uri;
    }

    if (port < last) {
        if (*port != ':') {
            u->err = "invalid host";
            return NGX_ERROR;
        }

        port++;

        len = last - port;

        if (u->listen) {
            dash = ngx_strlchr(port, last, '-');

            if (dash) {
                dash++;

                n = ngx_atoi(dash, last - dash);

                if (n < 1 || n > 65535) {
                    u->err = "invalid port";
                    return NGX_ERROR;
                }

                u->last_port = (in_port_t) n;

                len = dash - port - 1;
            }
        }

        n = ngx_atoi(port, len);

        if (n < 1 || n > 65535) {
            u->err = "invalid port";
            return NGX_ERROR;
        }

        if (u->last_port && n > u->last_port) {
            u->err = "invalid port range";
            return NGX_ERROR;
        }

        u->port = (in_port_t) n;
        sin6->sin6_port = htons((in_port_t) n);

        u->port_text.len = last - port;
        u->port_text.data = port;

    } else {
        u->no_port = 1;
        u->port = u->default_port;
        sin6->sin6_port = htons(u->default_port);
    }

    len = p - host;

    if (len == 0) {
        u->err = "no host";
        return NGX_ERROR;
    }

    u->host.len = len + 2;
    u->host.data = host - 1;

    if (ngx_inet6_addr(host, len, sin6->sin6_addr.s6_addr) != NGX_OK) {
        u->err = "invalid IPv6 address";
        return NGX_ERROR;
    }

    if (IN6_IS_ADDR_UNSPECIFIED(&sin6->sin6_addr)) {
        u->wildcard = 1;
    }

    u->family = AF_INET6;

    return ngx_inet_add_addr(pool, u, &u->sockaddr.sockaddr, u->socklen, 1);

#else

    u->err = "the INET6 sockets are not supported on this platform";

    return NGX_ERROR;

#endif
}