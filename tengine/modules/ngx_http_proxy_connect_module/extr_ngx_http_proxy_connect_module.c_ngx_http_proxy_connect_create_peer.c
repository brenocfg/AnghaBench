#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {void* sin6_port; } ;
struct TYPE_9__ {int socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_8__ {TYPE_2__ s_addr; } ;
struct sockaddr_in {void* sin_port; TYPE_1__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;
typedef  size_t ngx_int_t ;
struct TYPE_10__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_11__ {size_t naddrs; int socklen; TYPE_3__ host; struct sockaddr* sockaddr; int /*<<< orphan*/  port; TYPE_2__* addrs; } ;
typedef  TYPE_4__ ngx_http_upstream_resolved_t ;
struct TYPE_12__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_request_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  AF_INET6 128 
 size_t NGX_ERROR ; 
 size_t NGX_OK ; 
 int /*<<< orphan*/  NGX_SOCKADDR_STRLEN ; 
 size_t __ngx_sock_ntop (struct sockaddr*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr*,int /*<<< orphan*/ ,int) ; 
 struct sockaddr* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 struct sockaddr* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_random () ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_create_peer(ngx_http_request_t *r,
    ngx_http_upstream_resolved_t *ur)
{
    u_char                                      *p;
    ngx_int_t                                    i, len;
    socklen_t                                    socklen;
    struct sockaddr                             *sockaddr;

    i = ngx_random() % ur->naddrs;  /* i<-0 for ur->naddrs == 1 */

#if defined(nginx_version) && nginx_version >= 1005008

    socklen = ur->addrs[i].socklen;

    sockaddr = ngx_palloc(r->pool, socklen);
    if (sockaddr == NULL) {
        return NGX_ERROR;
    }

    ngx_memcpy(sockaddr, ur->addrs[i].sockaddr, socklen);

    switch (sockaddr->sa_family) {
#if (NGX_HAVE_INET6)
    case AF_INET6:
        ((struct sockaddr_in6 *) sockaddr)->sin6_port = htons(ur->port);
        break;
#endif
    default: /* AF_INET */
        ((struct sockaddr_in *) sockaddr)->sin_port = htons(ur->port);
    }

#else
    /* for nginx older than 1.5.8 */

    socklen = sizeof(struct sockaddr_in);

    sockaddr = ngx_pcalloc(r->pool, socklen);
    if (sockaddr == NULL) {
        return NGX_ERROR;
    }

    ((struct sockaddr_in *) sockaddr)->sin_family = AF_INET;
    ((struct sockaddr_in *) sockaddr)->sin_addr.s_addr = ur->addrs[i];
    ((struct sockaddr_in *) sockaddr)->sin_port = htons(ur->port);

#endif

    p = ngx_pnalloc(r->pool, NGX_SOCKADDR_STRLEN);
    if (p == NULL) {
        return NGX_ERROR;
    }

    len = __ngx_sock_ntop(sockaddr, socklen, p, NGX_SOCKADDR_STRLEN, 1);

    ur->sockaddr = sockaddr;
    ur->socklen = socklen;

    ur->host.data = p;
    ur->host.len = len;
    ur->naddrs = 1;

    return NGX_OK;
}