#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_46__   TYPE_9__ ;
typedef  struct TYPE_45__   TYPE_8__ ;
typedef  struct TYPE_44__   TYPE_7__ ;
typedef  struct TYPE_43__   TYPE_6__ ;
typedef  struct TYPE_42__   TYPE_5__ ;
typedef  struct TYPE_41__   TYPE_4__ ;
typedef  struct TYPE_40__   TYPE_3__ ;
typedef  struct TYPE_39__   TYPE_2__ ;
typedef  struct TYPE_38__   TYPE_1__ ;
typedef  struct TYPE_37__   TYPE_18__ ;
typedef  struct TYPE_36__   TYPE_15__ ;
typedef  struct TYPE_35__   TYPE_11__ ;
typedef  struct TYPE_34__   TYPE_10__ ;

/* Type definitions */
struct TYPE_37__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_42__ {int no_resolve; void* host; scalar_t__ no_port; scalar_t__ port; TYPE_1__* addrs; TYPE_18__ url; scalar_t__ err; scalar_t__ default_port; } ;
typedef  TYPE_5__ ngx_url_t ;
typedef  void* ngx_str_t ;
struct TYPE_43__ {int /*<<< orphan*/  timeout; TYPE_8__* data; int /*<<< orphan*/  handler; int /*<<< orphan*/  type; void* name; } ;
typedef  TYPE_6__ ngx_resolver_ctx_t ;
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_resolved_t ;
struct TYPE_41__ {scalar_t__ len; int /*<<< orphan*/ * data; } ;
struct TYPE_44__ {scalar_t__ method; TYPE_2__* main; TYPE_3__* connection; TYPE_4__ connect_host; scalar_t__ connect_port_n; int /*<<< orphan*/  pool; int /*<<< orphan*/  write_event_handler; int /*<<< orphan*/  read_event_handler; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_45__ {TYPE_15__* resolved; TYPE_9__* conf; } ;
typedef  TYPE_8__ ngx_http_proxy_connect_upstream_t ;
struct TYPE_46__ {scalar_t__ address; int /*<<< orphan*/  accept_connect; } ;
typedef  TYPE_9__ ngx_http_proxy_connect_loc_conf_t ;
struct TYPE_34__ {TYPE_8__* u; } ;
typedef  TYPE_10__ ngx_http_proxy_connect_ctx_t ;
struct TYPE_35__ {int /*<<< orphan*/  resolver_timeout; int /*<<< orphan*/  resolver; } ;
typedef  TYPE_11__ ngx_http_core_loc_conf_t ;
typedef  scalar_t__ in_port_t ;
struct TYPE_40__ {int /*<<< orphan*/  log; } ;
struct TYPE_39__ {int /*<<< orphan*/  count; } ;
struct TYPE_38__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
struct TYPE_36__ {int naddrs; void* host; TYPE_6__* ctx; scalar_t__ sockaddr; scalar_t__ no_port; scalar_t__ port; int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; } ;

/* Variables and functions */
 scalar_t__ NGX_DECLINED ; 
 scalar_t__ NGX_DONE ; 
 scalar_t__ NGX_HTTP_BAD_GATEWAY ; 
 scalar_t__ NGX_HTTP_CONNECT ; 
 scalar_t__ NGX_HTTP_FORBIDDEN ; 
 scalar_t__ NGX_HTTP_INTERNAL_SERVER_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 TYPE_6__* NGX_NO_RESOLVER ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_RESOLVE_A ; 
 scalar_t__ ngx_http_complex_value (TYPE_7__*,scalar_t__,TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_10__* ngx_http_get_module_ctx (TYPE_7__*,int /*<<< orphan*/ ) ; 
 void* ngx_http_get_module_loc_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_http_proxy_connect_allow_handler (TYPE_7__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_module ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_process_connect (TYPE_7__*,TYPE_8__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_rd_check_broken_connection ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_resolve_handler ; 
 scalar_t__ ngx_http_proxy_connect_sock_ntop (TYPE_7__*,TYPE_8__*) ; 
 scalar_t__ ngx_http_proxy_connect_upstream_create (TYPE_7__*,TYPE_10__*) ; 
 int /*<<< orphan*/  ngx_http_proxy_connect_wr_check_broken_connection ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_18__*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_15__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_resolve_name (TYPE_6__*) ; 
 TYPE_6__* ngx_resolve_start (int /*<<< orphan*/ ,TYPE_6__*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_connect_handler(ngx_http_request_t *r)
{
    ngx_url_t                            url;
    ngx_int_t                            rc;
    ngx_resolver_ctx_t                  *rctx, temp;
    ngx_http_core_loc_conf_t            *clcf;
    ngx_http_proxy_connect_ctx_t        *ctx;
    ngx_http_proxy_connect_upstream_t   *u;
    ngx_http_proxy_connect_loc_conf_t   *plcf;

    plcf = ngx_http_get_module_loc_conf(r, ngx_http_proxy_connect_module);

    if (r->method != NGX_HTTP_CONNECT || !plcf->accept_connect) {
        return NGX_DECLINED;
    }

    rc = ngx_http_proxy_connect_allow_handler(r, plcf);

    if (rc != NGX_OK) {
        return rc;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_proxy_connect_module);;

    if (ngx_http_proxy_connect_upstream_create(r, ctx) != NGX_OK) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    u = ctx->u;

    u->conf = plcf;

    ngx_memzero(&url, sizeof(ngx_url_t));

    if (plcf->address) {
        if (ngx_http_complex_value(r, plcf->address, &url.url) != NGX_OK) {
            return NGX_HTTP_INTERNAL_SERVER_ERROR;
        }

        if (url.url.len == 0 || url.url.data == NULL) {
            url.url.len = r->connect_host.len;
            url.url.data = r->connect_host.data;
        }

    } else {
        url.url.len = r->connect_host.len;
        url.url.data = r->connect_host.data;
    }

    url.default_port = r->connect_port_n;
    url.no_resolve = 1;

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "proxy_connect: connect handler: parse url: %V" , &url.url);

    if (ngx_parse_url(r->pool, &url) != NGX_OK) {
        if (url.err) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "proxy_connect: %s in connect host \"%V\"",
                          url.err, &url.url);
            return NGX_HTTP_FORBIDDEN;
        }

        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    r->read_event_handler = ngx_http_proxy_connect_rd_check_broken_connection;
    r->write_event_handler = ngx_http_proxy_connect_wr_check_broken_connection;

    /* NOTE:
     *   We use only one address in u->resolved,
     *   and u->resolved.host is "<address:port>" format.
     */

    u->resolved = ngx_pcalloc(r->pool, sizeof(ngx_http_upstream_resolved_t));
    if (u->resolved == NULL) {
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    /* rc = NGX_DECLINED */

    if (url.addrs) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "proxy_connect: upstream address given directly");

        u->resolved->sockaddr = url.addrs[0].sockaddr;
        u->resolved->socklen = url.addrs[0].socklen;
#if defined(nginx_version) && nginx_version >= 1011007
        u->resolved->name = url.addrs[0].name;
#endif
        u->resolved->naddrs = 1;
    }

    u->resolved->host = url.host;
    u->resolved->port = (in_port_t) (url.no_port ? r->connect_port_n : url.port);
    u->resolved->no_port = url.no_port;

    if (u->resolved->sockaddr) {

        rc = ngx_http_proxy_connect_sock_ntop(r, u);

        if (rc != NGX_OK) {
            return rc;
        }

        r->main->count++;

        ngx_http_proxy_connect_process_connect(r, u);

        return NGX_DONE;
    }

    ngx_str_t *host = &url.host;

    clcf = ngx_http_get_module_loc_conf(r, ngx_http_core_module);
    temp.name = *host;

    rctx = ngx_resolve_start(clcf->resolver, &temp);
    if (rctx == NULL) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "proxy_connect: failed to start the resolver");
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    if (rctx == NGX_NO_RESOLVER) {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "proxy_connect: no resolver defined to resolve %V",
                      &r->connect_host);
        return NGX_HTTP_BAD_GATEWAY;
    }

    rctx->name = *host;
#if !defined(nginx_version) || nginx_version < 1005008
    rctx->type = NGX_RESOLVE_A;
#endif
    rctx->handler = ngx_http_proxy_connect_resolve_handler;
    rctx->data = u;
    rctx->timeout = clcf->resolver_timeout;

    u->resolved->ctx = rctx;

    r->main->count++;

    if (ngx_resolve_name(rctx) != NGX_OK) {
        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                       "proxy_connect: fail to run resolver immediately");

        u->resolved->ctx = NULL;
        r->main->count--;
        return NGX_HTTP_INTERNAL_SERVER_ERROR;
    }

    return NGX_DONE;
}