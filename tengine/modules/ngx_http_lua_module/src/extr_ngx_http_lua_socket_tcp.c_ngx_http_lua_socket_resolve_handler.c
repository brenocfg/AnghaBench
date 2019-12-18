#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_33__   TYPE_9__ ;
typedef  struct TYPE_32__   TYPE_8__ ;
typedef  struct TYPE_31__   TYPE_7__ ;
typedef  struct TYPE_30__   TYPE_6__ ;
typedef  struct TYPE_29__   TYPE_5__ ;
typedef  struct TYPE_28__   TYPE_4__ ;
typedef  struct TYPE_27__   TYPE_3__ ;
typedef  struct TYPE_26__   TYPE_2__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_12__ ;
typedef  struct TYPE_23__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct sockaddr_in6 {void* sin6_port; } ;
struct TYPE_24__ {int socklen; struct sockaddr* sockaddr; } ;
struct TYPE_25__ {TYPE_12__ s_addr; } ;
struct sockaddr_in {TYPE_1__ sin_addr; void* sin_port; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int sa_family; } ;
typedef  int socklen_t ;
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
struct TYPE_28__ {int /*<<< orphan*/  len; scalar_t__ data; } ;
struct TYPE_29__ {int naddrs; TYPE_12__* addrs; scalar_t__ state; TYPE_4__ name; TYPE_8__* data; } ;
typedef  TYPE_5__ ngx_resolver_ctx_t ;
struct TYPE_26__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_30__ {int naddrs; int socklen; int /*<<< orphan*/ * ctx; TYPE_2__ host; struct sockaddr* sockaddr; TYPE_12__* addrs; int /*<<< orphan*/  port; } ;
typedef  TYPE_6__ ngx_http_upstream_resolved_t ;
struct TYPE_31__ {int /*<<< orphan*/  (* write_event_handler ) (TYPE_7__*) ;int /*<<< orphan*/  pool; TYPE_10__* connection; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_32__ {unsigned int conn_waiting; void* write_prepare_retvals; TYPE_3__* write_co_ctx; TYPE_6__* resolved; TYPE_7__* request; } ;
typedef  TYPE_8__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_33__ {int /*<<< orphan*/  resume_handler; TYPE_3__* cur_co_ctx; } ;
typedef  TYPE_9__ ngx_http_lua_ctx_t ;
struct TYPE_23__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_10__ ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int in_addr_t ;
struct TYPE_27__ {int /*<<< orphan*/ * co; int /*<<< orphan*/ * cleanup; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
#define  AF_INET6 128 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_NOMEM ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_RESOLVER ; 
 int NGX_INET_ADDRSTRLEN ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_SOCKADDR_STRLEN ; 
 int /*<<< orphan*/  dd (char*,...) ; 
 void* htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushfstring (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 TYPE_9__* ngx_http_get_module_ctx (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_assert (int) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 void* ngx_http_lua_socket_conn_error_retval_handler ; 
 int /*<<< orphan*/  ngx_http_lua_socket_handle_conn_error (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_resolve_retval_handler (TYPE_7__*,TYPE_8__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_conn_resume ; 
 int /*<<< orphan*/  ngx_http_run_posted_requests (TYPE_10__*) ; 
 size_t ngx_inet_ntop (int /*<<< orphan*/ ,TYPE_12__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_debug4 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int,int,int) ; 
 int /*<<< orphan*/  ngx_memcpy (struct sockaddr*,struct sockaddr*,int) ; 
 int /*<<< orphan*/  ngx_memzero (struct sockaddr_in*,int) ; 
 struct sockaddr* ngx_palloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_pnalloc (int /*<<< orphan*/ ,size_t) ; 
 size_t ngx_random () ; 
 int /*<<< orphan*/  ngx_resolve_name_done (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_resolver_strerror (scalar_t__) ; 
 void* ngx_sock_ntop (struct sockaddr*,int,int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/ * ngx_sprintf (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int ntohl (TYPE_12__) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*) ; 

__attribute__((used)) static void
ngx_http_lua_socket_resolve_handler(ngx_resolver_ctx_t *ctx)
{
    ngx_http_request_t                  *r;
    ngx_connection_t                    *c;
    ngx_http_upstream_resolved_t        *ur;
    ngx_http_lua_ctx_t                  *lctx;
    lua_State                           *L;
    ngx_http_lua_socket_tcp_upstream_t  *u;
    u_char                              *p;
    size_t                               len;
#if defined(nginx_version) && nginx_version >= 1005008
    socklen_t                            socklen;
    struct sockaddr                     *sockaddr;
#else
    struct sockaddr_in                  *sin;
#endif
    ngx_uint_t                           i;
    unsigned                             waiting;

    u = ctx->data;
    r = u->request;
    c = r->connection;
    ur = u->resolved;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, c->log, 0,
                   "lua tcp socket resolve handler");

    lctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (lctx == NULL) {
        return;
    }

    lctx->cur_co_ctx = u->write_co_ctx;

    u->write_co_ctx->cleanup = NULL;

    L = lctx->cur_co_ctx->co;

    waiting = u->conn_waiting;

    if (ctx->state) {
        ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, 0,
                       "lua tcp socket resolver error: %s "
                       "(connect waiting: %d)",
                       ngx_resolver_strerror(ctx->state), (int) waiting);

        lua_pushnil(L);
        lua_pushlstring(L, (char *) ctx->name.data, ctx->name.len);
        lua_pushfstring(L, " could not be resolved (%d: %s)",
                        (int) ctx->state,
                        ngx_resolver_strerror(ctx->state));
        lua_concat(L, 2);

        u->write_prepare_retvals =
                                ngx_http_lua_socket_conn_error_retval_handler;
        ngx_http_lua_socket_handle_conn_error(r, u,
                                              NGX_HTTP_LUA_SOCKET_FT_RESOLVER);

        if (waiting) {
            ngx_http_run_posted_requests(c);
        }

        return;
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
        dd("addr i: %d %p", (int) i,  &ctx->addrs[i]);

        addr = ntohl(ctx->addrs[i]);

        ngx_log_debug4(NGX_LOG_DEBUG_HTTP, c->log, 0,
                       "name was resolved to %ud.%ud.%ud.%ud",
                       (addr >> 24) & 0xff, (addr >> 16) & 0xff,
                       (addr >> 8) & 0xff, addr & 0xff);
    }
#   endif
    }
#endif

    ngx_http_lua_assert(ur->naddrs > 0);

    if (ur->naddrs == 1) {
        i = 0;

    } else {
        i = ngx_random() % ur->naddrs;
    }

    dd("selected addr index: %d", (int) i);

#if defined(nginx_version) && nginx_version >= 1005008
    socklen = ur->addrs[i].socklen;

    sockaddr = ngx_palloc(r->pool, socklen);
    if (sockaddr == NULL) {
        goto nomem;
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
        goto nomem;
    }

    len = ngx_sock_ntop(sockaddr, socklen, p, NGX_SOCKADDR_STRLEN, 1);
    ur->sockaddr = sockaddr;
    ur->socklen = socklen;

#else
    /* for nginx older than 1.5.8 */

    len = NGX_INET_ADDRSTRLEN + sizeof(":65535") - 1;

    p = ngx_pnalloc(r->pool, len + sizeof(struct sockaddr_in));
    if (p == NULL) {
        goto nomem;
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

    u->conn_waiting = 0;
    u->write_co_ctx = NULL;

    if (waiting) {
        lctx->resume_handler = ngx_http_lua_socket_tcp_conn_resume;
        r->write_event_handler(r);
        ngx_http_run_posted_requests(c);

    } else {
        (void) ngx_http_lua_socket_resolve_retval_handler(r, u, L);
    }

    return;

nomem:

    if (ur->ctx) {
        ngx_resolve_name_done(ctx);
        ur->ctx = NULL;
    }

    u->write_prepare_retvals = ngx_http_lua_socket_conn_error_retval_handler;
    ngx_http_lua_socket_handle_conn_error(r, u,
                                          NGX_HTTP_LUA_SOCKET_FT_NOMEM);

    if (waiting) {
        dd("run posted requests");
        ngx_http_run_posted_requests(c);

    } else {
        lua_pushnil(L);
        lua_pushliteral(L, "no memory");
    }
}