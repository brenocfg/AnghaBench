#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_8__ ;
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int u_long ;
typedef  int u_char ;
struct in6_addr {int* s6_addr; } ;
struct sockaddr_in6 {struct in6_addr sin6_addr; } ;
struct TYPE_17__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_4__ sin_addr; } ;
struct TYPE_20__ {scalar_t__ nelts; } ;
struct TYPE_15__ {TYPE_7__ x_forwarded_for; } ;
struct TYPE_18__ {TYPE_2__ headers_in; TYPE_1__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_19__ {int /*<<< orphan*/  proxy_recursive; int /*<<< orphan*/ * proxies; } ;
typedef  TYPE_6__ ngx_http_geoip_conf_t ;
typedef  TYPE_7__ ngx_array_t ;
struct TYPE_21__ {TYPE_3__* sockaddr; int /*<<< orphan*/  socklen; } ;
typedef  TYPE_8__ ngx_addr_t ;
typedef  int in_addr_t ;
struct TYPE_16__ {scalar_t__ sa_family; } ;
struct TYPE_14__ {int /*<<< orphan*/  socklen; TYPE_3__* sockaddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ IN6_IS_ADDR_V4MAPPED (struct in6_addr*) ; 
 int INADDR_NONE ; 
 int /*<<< orphan*/  ngx_http_get_forwarded_addr (TYPE_5__*,TYPE_8__*,TYPE_7__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static u_long
ngx_http_geoip_addr(ngx_http_request_t *r, ngx_http_geoip_conf_t *gcf)
{
    ngx_addr_t           addr;
    ngx_array_t         *xfwd;
    struct sockaddr_in  *sin;

    addr.sockaddr = r->connection->sockaddr;
    addr.socklen = r->connection->socklen;
    /* addr.name = r->connection->addr_text; */

    xfwd = &r->headers_in.x_forwarded_for;

    if (xfwd->nelts > 0 && gcf->proxies != NULL) {
        (void) ngx_http_get_forwarded_addr(r, &addr, xfwd, NULL,
                                           gcf->proxies, gcf->proxy_recursive);
    }

#if (NGX_HAVE_INET6)

    if (addr.sockaddr->sa_family == AF_INET6) {
        u_char           *p;
        in_addr_t         inaddr;
        struct in6_addr  *inaddr6;

        inaddr6 = &((struct sockaddr_in6 *) addr.sockaddr)->sin6_addr;

        if (IN6_IS_ADDR_V4MAPPED(inaddr6)) {
            p = inaddr6->s6_addr;

            inaddr = p[12] << 24;
            inaddr += p[13] << 16;
            inaddr += p[14] << 8;
            inaddr += p[15];

            return inaddr;
        }
    }

#endif

    if (addr.sockaddr->sa_family != AF_INET) {
        return INADDR_NONE;
    }

    sin = (struct sockaddr_in *) addr.sockaddr;
    return ntohl(sin->sin_addr.s_addr);
}