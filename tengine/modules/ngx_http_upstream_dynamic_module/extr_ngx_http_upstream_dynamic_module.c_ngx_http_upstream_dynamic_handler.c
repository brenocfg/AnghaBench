#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_28__   TYPE_9__ ;
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {void* sin6_port; } ;
struct TYPE_22__ {scalar_t__ s_addr; } ;
struct sockaddr_in {int sa_family; TYPE_3__ sin_addr; void* sin_port; } ;
struct sockaddr {int sa_family; TYPE_3__ sin_addr; void* sin_port; } ;
typedef  int socklen_t ;
typedef  size_t ngx_uint_t ;
struct TYPE_23__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_4__ ngx_str_t ;
struct TYPE_24__ {size_t naddrs; TYPE_2__* addrs; scalar_t__ state; int /*<<< orphan*/  name; TYPE_9__* data; } ;
typedef  TYPE_5__ ngx_resolver_ctx_t ;
struct TYPE_25__ {int socklen; void* resolved; TYPE_4__* name; struct sockaddr_in* sockaddr; } ;
typedef  TYPE_6__ ngx_peer_connection_t ;
struct TYPE_26__ {int /*<<< orphan*/ * dyn_resolve_ctx; TYPE_6__ peer; } ;
typedef  TYPE_7__ ngx_http_upstream_t ;
struct TYPE_27__ {scalar_t__ fail_check; } ;
typedef  TYPE_8__ ngx_http_upstream_dynamic_srv_conf_t ;
struct TYPE_28__ {TYPE_8__* conf; TYPE_10__* request; } ;
typedef  TYPE_9__ ngx_http_upstream_dynamic_peer_data_t ;
struct TYPE_19__ {TYPE_1__* connection; int /*<<< orphan*/  pool; TYPE_7__* upstream; } ;
typedef  TYPE_10__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  in_port_t ;
struct TYPE_21__ {int socklen; struct sockaddr_in* sockaddr; } ;
struct TYPE_20__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  AF_INET6 128 
 int /*<<< orphan*/  NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 void* NGX_HTTP_UPSTREAM_DR_FAILED ; 
 void* NGX_HTTP_UPSTREAM_DR_OK ; 
 int NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int NGX_SOCKADDR_STRLEN ; 
 void* htons (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_cmp_sockaddr (struct sockaddr_in*,int,struct sockaddr_in*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_upstream_connect (TYPE_10__*,TYPE_7__*) ; 
 int /*<<< orphan*/  ngx_http_upstream_finalize_request (TYPE_10__*,TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_inet_get_port (struct sockaddr_in*) ; 
 size_t ngx_inet_ntop (int /*<<< orphan*/ ,scalar_t__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr_in*,struct sockaddr_in*,int) ; 
 TYPE_4__* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 struct sockaddr_in* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 void* ngx_sock_ntop (struct sockaddr_in*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_time () ; 
 int /*<<< orphan*/  ntohs (void*) ; 

__attribute__((used)) static void
ngx_http_upstream_dynamic_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_http_request_t                    *r;
    ngx_http_upstream_t                   *u;
    ngx_peer_connection_t                 *pc;
#if defined(nginx_version) && nginx_version >= 1005008
    socklen_t                              socklen;
    struct sockaddr                       *sockaddr, *csockaddr;
#else
    struct sockaddr_in                    *sin, *csin;
#endif
    in_port_t                              port;
    ngx_str_t                             *addr;
    u_char                                *p;

    size_t                                 len;
    ngx_http_upstream_dynamic_srv_conf_t  *dscf;
    ngx_http_upstream_dynamic_peer_data_t *bp;

    bp = ctx->data;
    r = bp->request;
    u = r->upstream;
    pc = &u->peer;
    dscf = bp->conf;

    if (ctx->state) {

        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "%V could not be resolved (%i: %s)",
                      &ctx->name, ctx->state,
                      ngx_resolver_strerror(ctx->state));

        dscf->fail_check = ngx_time();

        pc->resolved = NGX_HTTP_UPSTREAM_DR_FAILED;

    } else {
        /* dns query ok */
#if (NGX_DEBUG)
        {
        u_char      text[NGX_SOCKADDR_STRLEN];
        ngx_str_t   addr;
        ngx_uint_t  i;

        addr.data = text;

        for (i = 0; i < ctx->naddrs; i++) {
            addr.len = ngx_sock_ntop(ctx->addrs[i].sockaddr, ctx->addrs[i].socklen,
                                     text, NGX_SOCKADDR_STRLEN, 0);

            ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                           "name was resolved to %V", &addr);
        }
        }
#endif
        dscf->fail_check = 0;
#if defined(nginx_version) && nginx_version >= 1005008
        csockaddr = ctx->addrs[0].sockaddr;
        socklen = ctx->addrs[0].socklen;

        if (ngx_cmp_sockaddr(pc->sockaddr, pc->socklen, csockaddr, socklen, 0)
            == NGX_OK)
        {
            pc->resolved = NGX_HTTP_UPSTREAM_DR_OK;
            goto out;
        }

        sockaddr = ngx_pcalloc(r->pool, socklen);
        if (sockaddr == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        ngx_memcpy(sockaddr, csockaddr, socklen);
        port = ngx_inet_get_port(pc->sockaddr);
        
        switch (sockaddr->sa_family) {
#if (NGX_HAVE_INET6)
        case AF_INET6:
            ((struct sockaddr_in6 *) sockaddr)->sin6_port = htons(port);
            break;
#endif
        default: /* AF_INET */
            ((struct sockaddr_in *) sockaddr)->sin_port = htons(port);
        }

        p = ngx_pnalloc(r->pool, NGX_SOCKADDR_STRLEN);
        if (p == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        len = ngx_sock_ntop(sockaddr, socklen, p, NGX_SOCKADDR_STRLEN, 1);

        addr = ngx_palloc(r->pool, sizeof(ngx_str_t));
        if (addr == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        addr->data = p;
        addr->len = len;
        pc->sockaddr = sockaddr;
        pc->socklen = socklen;
        pc->name = addr;

#else
        /* for nginx older than 1.5.8 */

        sin = ngx_pcalloc(r->pool, sizeof(struct sockaddr_in));
        if (sin == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        ngx_memcpy(sin, pc->sockaddr, pc->socklen);

        /* only the first IP addr is used in version 1 */

        csin = (struct sockaddr_in *) ctx->addrs[0].sockaddr;
        if (sin->sin_addr.s_addr == csin->sin_addr.s_addr) {

            pc->resolved = NGX_HTTP_UPSTREAM_DR_OK;

            goto out;
        }

        sin->sin_addr.s_addr = csin->sin_addr.s_addr;

        len = NGX_INET_ADDRSTRLEN + sizeof(":65535") - 1;

        p = ngx_pnalloc(r->pool, len);
        if (p == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        port = ntohs(sin->sin_port);
        len = ngx_inet_ntop(AF_INET, &sin->sin_addr.s_addr,
                            p, NGX_INET_ADDRSTRLEN);
        len = ngx_sprintf(&p[len], ":%d", port) - p;

        addr = ngx_palloc(r->pool, sizeof(ngx_str_t));
        if (addr == NULL) {
            ngx_http_upstream_finalize_request(r, u,
                                               NGX_HTTP_INTERNAL_SERVER_ERROR);
            return;
        }

        addr->data = p;
        addr->len = len;

        pc->sockaddr = (struct sockaddr *) sin;
        pc->socklen = sizeof(struct sockaddr_in);
        pc->name = addr;
#endif

        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                "name was resolved to %V", pc->name);

        pc->resolved = NGX_HTTP_UPSTREAM_DR_OK;
    }

out:
    ngx_resolve_name_done(ctx);
    u->dyn_resolve_ctx = NULL;

    ngx_http_upstream_connect(r, u);
}