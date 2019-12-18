#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  size_t ngx_uint_t ;
struct TYPE_18__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_19__ {size_t async; size_t naddrs; TYPE_7__* addrs; scalar_t__ state; int /*<<< orphan*/  name; TYPE_5__* data; } ;
typedef  TYPE_2__ ngx_resolver_ctx_t ;
struct TYPE_20__ {size_t naddrs; int /*<<< orphan*/ * ctx; TYPE_7__* addrs; } ;
typedef  TYPE_3__ ngx_http_upstream_resolved_t ;
struct TYPE_21__ {TYPE_6__* connection; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_22__ {TYPE_3__* resolved; TYPE_4__* request; } ;
typedef  TYPE_5__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_6__ ngx_connection_t ;
typedef  int in_addr_t ;
struct TYPE_24__ {int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_HTTP_BAD_GATEWAY ; 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 scalar_t__ ngx_http_proxy_connect_create_peer (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_finalize_request (TYPE_4__*,TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_process_connect (TYPE_4__*,TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 int /*<<< orphan*/  ngx_sock_ntop (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int ntohl (TYPE_7__) ; 

__attribute__((used)) static void
ngx_http_proxy_connect_resolve_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_connection_t                            *c;
    ngx_http_request_t                          *r;
    ngx_http_upstream_resolved_t                *ur;
    ngx_http_proxy_connect_upstream_t           *u;

#if defined(nginx_version) && nginx_version >= 1013002
    ngx_uint_t run_posted = ctx->async;
#endif

    u = ctx->data;
    r = u->request;
    ur = u->resolved;
    c = r->connection;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect: resolve handler");

    if (ctx->state) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "proxy_connect: %V could not be resolved (%i: %s)",
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
    ngx_uint_t  i;
    ngx_str_t   addr;
    u_char      text[NGX_SOCKADDR_STRLEN];

    addr.data = text;

    for (i = 0; i < ctx->naddrs; i++) {
        addr.len = ngx_sock_ntop(ur->addrs[i].sockaddr, ur->addrs[i].socklen,
                                 text, NGX_SOCKADDR_STRLEN, 0);

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "proxy_connect: name was resolved to %V", &addr);
    }
#   else
    ngx_uint_t  i;
    in_addr_t   addr;

    for (i = 0; i < ctx->naddrs; i++) {
        addr = ntohl(ctx->addrs[i]);

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, c->log, 0,
                       "proxy_connect: name was resolved to %ud.%ud.%ud.%ud",
                       (addr >> 24) & 0xff, (addr >> 16) & 0xff,
                       (addr >> 8) & 0xff, addr & 0xff);
    }
#   endif
    }
#endif

    if (ngx_http_proxy_connect_create_peer(r, ur) != NGX_OK) {
        ngx_http_proxy_connect_finalize_request(r, u,
                                                NGX_HTTP_INTERNAL_SERVER_ERROR);
        goto failed;
    }

    ngx_resolve_name_done(ctx);
    ur->ctx = NULL;

    ngx_http_proxy_connect_process_connect(r, u);

failed:

#if defined(nginx_version) && nginx_version >= 1013002
    if (run_posted) {
        ngx_http_run_posted_requests(c);
    }
#else
    ngx_http_run_posted_requests(c);
#endif
}