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
struct TYPE_15__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_17__ {int no_resolve; char* err; TYPE_2__* addrs; scalar_t__ uri_part; scalar_t__ default_port; TYPE_1__ url; } ;
typedef  TYPE_3__ ngx_url_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_t ;
struct TYPE_18__ {int /*<<< orphan*/  pool; int /*<<< orphan*/ * upstream; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_19__ {TYPE_7__* balancer_peer_data; } ;
typedef  TYPE_5__ ngx_http_lua_main_conf_t ;
struct TYPE_20__ {int context; } ;
typedef  TYPE_6__ ngx_http_lua_ctx_t ;
struct TYPE_21__ {int /*<<< orphan*/ * host; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;
typedef  TYPE_7__ ngx_http_lua_balancer_peer_data_t ;
typedef  scalar_t__ in_port_t ;
struct TYPE_16__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; scalar_t__ sockaddr; } ;

/* Variables and functions */
 int NGX_ERROR ; 
 int NGX_HTTP_LUA_CONTEXT_BALANCER ; 
 scalar_t__ NGX_OK ; 
 TYPE_6__* ngx_http_get_module_ctx (TYPE_4__*,int /*<<< orphan*/ ) ; 
 TYPE_5__* ngx_http_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/  const*,size_t) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_3__*) ; 

int
ngx_http_lua_ffi_balancer_set_current_peer(ngx_http_request_t *r,
    const u_char *addr, size_t addr_len, int port, char **err)
{
    ngx_url_t              url;
    ngx_http_lua_ctx_t    *ctx;
    ngx_http_upstream_t   *u;

    ngx_http_lua_main_conf_t           *lmcf;
    ngx_http_lua_balancer_peer_data_t  *bp;

    if (r == NULL) {
        *err = "no request found";
        return NGX_ERROR;
    }

    u = r->upstream;

    if (u == NULL) {
        *err = "no upstream found";
        return NGX_ERROR;
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);
    if (ctx == NULL) {
        *err = "no ctx found";
        return NGX_ERROR;
    }

    if ((ctx->context & NGX_HTTP_LUA_CONTEXT_BALANCER) == 0) {
        *err = "API disabled in the current context";
        return NGX_ERROR;
    }

    lmcf = ngx_http_get_module_main_conf(r, ngx_http_lua_module);

    /* we cannot read r->upstream->peer.data here directly because
     * it could be overridden by other modules like
     * ngx_http_upstream_keepalive_module.
     */
    bp = lmcf->balancer_peer_data;
    if (bp == NULL) {
        *err = "no upstream peer data found";
        return NGX_ERROR;
    }

    ngx_memzero(&url, sizeof(ngx_url_t));

    url.url.data = ngx_palloc(r->pool, addr_len);
    if (url.url.data == NULL) {
        *err = "no memory";
        return NGX_ERROR;
    }

    ngx_memcpy(url.url.data, addr, addr_len);

    url.url.len = addr_len;
    url.default_port = (in_port_t) port;
    url.uri_part = 0;
    url.no_resolve = 1;

    if (ngx_parse_url(r->pool, &url) != NGX_OK) {
        if (url.err) {
            *err = url.err;
        }

        return NGX_ERROR;
    }

    if (url.addrs && url.addrs[0].sockaddr) {
        bp->sockaddr = url.addrs[0].sockaddr;
        bp->socklen = url.addrs[0].socklen;
        bp->host = &url.addrs[0].name;

    } else {
        *err = "no host allowed";
        return NGX_ERROR;
    }

    return NGX_OK;
}