#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_15__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; int /*<<< orphan*/  sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct TYPE_17__ {int naddrs; int /*<<< orphan*/  name; int /*<<< orphan*/ * addrs; scalar_t__ state; TYPE_6__* data; } ;
typedef  TYPE_3__ ngx_resolver_ctx_t ;
typedef  size_t ngx_int_t ;
struct TYPE_16__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_18__ {int naddrs; int socklen; int /*<<< orphan*/ * ctx; TYPE_2__ host; struct sockaddr* sockaddr; int /*<<< orphan*/ * addrs; int /*<<< orphan*/  port; } ;
typedef  TYPE_4__ ngx_http_upstream_resolved_t ;
struct TYPE_19__ {int /*<<< orphan*/  pool; TYPE_7__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_20__ {TYPE_4__* resolved; TYPE_5__* request; } ;
typedef  TYPE_6__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_21__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_7__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int /*<<< orphan*/  htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_5__*,TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_process_connect (TYPE_5__*,TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_7__*) ; 
 size_t ngx_inet_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,...) ; 
 int /*<<< orphan*/  ngx_memzero (struct sockaddr_in*,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 size_t ngx_random () ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_resolve_handler(ngx_resolver_ctx_t *ctx)
{
    u_char                                      *p;
    ngx_int_t                                    i, len;
    ngx_connection_t                            *c;
#if defined(nginx_version) && nginx_version >= 1005008
    socklen_t                                    socklen;
    struct sockaddr                             *sockaddr;
#else
    struct sockaddr_in                          *sin;
#endif
    ngx_http_request_t                          *r;
    ngx_http_upstream_resolved_t                *ur;
    ngx_http_proxy_connect_upstream_t           *u;

    u = ctx->data;
    r = u->request;
    ur = u->resolved;
    c = r->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect resolve handler");

    if (ctx->state) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "%V could not be resolved (%i: %s)",
                      &ctx->name, ctx->state,
                      ngx_resolver_strerror(ctx->state));

        ngx_http_proxy_connect_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
        goto failed;
    }

    ur->naddrs = ctx->naddrs;
    ur->addrs = ctx->addrs;

#if (NGX_DEBUG)
    {
#   if defined(nginx_version) && nginx_version >= 1005008
    u_char      text[NGX_SOCKADDR_STRLEN];
    ngx_str_t   addr;
#   else
    in_addr_t   addr;
#   endif
    ngx_uint_t  i;

#   if defined(nginx_version) && nginx_version >= 1005008
    addr.data = text;

    for (i = 0; i < ctx->naddrs; i++) {
        addr.len = ngx_sock_ntop(ur->addrs[i].sockaddr, ur->addrs[i].socklen,
                                 text, NGX_SOCKADDR_STRLEN, 0);

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "name was resolved to %V", &addr);
    }
#   else
    for (i = 0; i < ctx->naddrs; i++) {
        addr = ntohl(ctx->addrs[i]);

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, c->log, 0,
                       "name was resolved to %ud.%ud.%ud.%ud",
                       (addr >> 24) & 0xff, (addr >> 16) & 0xff,
                       (addr >> 8) & 0xff, addr & 0xff);
    }
#   endif
    }
#endif

    if (ur->naddrs == 0) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "%V could not be resolved", &ctx->name);

        ngx_http_proxy_connect_finalize_request(r, u, NGX_HTTP_BAD_GATEWAY);
        goto failed;
    }

    if (ur->naddrs == 1) {
        i = 0;

    } else {
        i = ngx_random() % ur->naddrs;
    }

#if defined(nginx_version) && nginx_version >= 1005008
    socklen = ur->addrs[i].socklen;

    sockaddr = ngx_palloc(r->pool, socklen);
    if (sockaddr == NULL) {
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);

        return;
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

    p = ngx_pnalloc(r->pool, NGX_SOCKADDR_STRLEN);
    if (p == NULL) {
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);

        return;
    }

    len = ngx_sock_ntop(sockaddr, socklen, p, NGX_SOCKADDR_STRLEN, 1);
    ur->sockaddr = sockaddr;
    ur->socklen = socklen;

#else
    /* for nginx older than 1.5.8 */

    len = NGX_INET_ADDRSTRLEN + sizeof(":65536") - 1;

    p = ngx_pnalloc(r->pool, len + sizeof(struct sockaddr_in));
    if (p == NULL) {
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);

        return;
    }

    sin = (struct sockaddr_in *) &p[len];
    ngx_memzero(sin, sizeof(struct sockaddr_in));

    len = ngx_inet_ntop(AF_INET, &ur->addrs[i], p, NGX_INET_ADDRSTRLEN);
    len = ngx_sprintf(&p[len], ":%d", ur->port) - p;

    sin->sin_family = AF_INET;
    sin->sin_port = htons(ur->port);
    sin->sin_addr.s_addr = ur->addrs[i];

    ur->sockaddr = (struct sockaddr *) sin;
    ur->socklen = sizeof(struct sockaddr_in);
#endif

    ur->host.data = p;
    ur->host.len = len;
    ur->naddrs = 1;

    ngx_resolve_name_done(ctx);
    ur->ctx = NULL;

    ngx_http_proxy_connect_process_connect(r, u);

failed:

    ngx_http_run_posted_requests(c);
}