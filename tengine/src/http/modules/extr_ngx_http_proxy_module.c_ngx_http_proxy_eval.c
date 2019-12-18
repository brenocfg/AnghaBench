#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_39__   TYPE_9__ ;
typedef  struct TYPE_38__   TYPE_8__ ;
typedef  struct TYPE_37__   TYPE_7__ ;
typedef  struct TYPE_36__   TYPE_6__ ;
typedef  struct TYPE_35__   TYPE_5__ ;
typedef  struct TYPE_34__   TYPE_4__ ;
typedef  struct TYPE_33__   TYPE_3__ ;
typedef  struct TYPE_32__   TYPE_2__ ;
typedef  struct TYPE_31__   TYPE_21__ ;
typedef  struct TYPE_30__   TYPE_1__ ;
typedef  struct TYPE_29__   TYPE_14__ ;
typedef  struct TYPE_28__   TYPE_13__ ;
typedef  struct TYPE_27__   TYPE_12__ ;
typedef  struct TYPE_26__   TYPE_11__ ;
typedef  struct TYPE_25__   TYPE_10__ ;

/* Type definitions */
typedef  int u_short ;
typedef  char u_char ;
struct TYPE_34__ {char* data; scalar_t__ len; } ;
struct TYPE_37__ {size_t len; scalar_t__ data; } ;
struct TYPE_38__ {int default_port; int uri_part; int no_resolve; int port; scalar_t__ no_port; int /*<<< orphan*/  host; TYPE_6__* addrs; TYPE_4__ uri; TYPE_7__ url; int /*<<< orphan*/  err; } ;
typedef  TYPE_8__ ngx_url_t ;
struct TYPE_39__ {int len; scalar_t__ data; } ;
typedef  TYPE_9__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_35__ {size_t len; scalar_t__ data; } ;
struct TYPE_25__ {int ssl; TYPE_14__* resolved; TYPE_5__ schema; } ;
typedef  TYPE_10__ ngx_http_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_resolved_t ;
struct TYPE_26__ {int /*<<< orphan*/  pool; TYPE_3__* connection; TYPE_10__* upstream; } ;
typedef  TYPE_11__ ngx_http_request_t ;
struct TYPE_27__ {TYPE_2__* proxy_values; TYPE_1__* proxy_lengths; } ;
typedef  TYPE_12__ ngx_http_proxy_loc_conf_t ;
struct TYPE_31__ {TYPE_5__ key_start; } ;
struct TYPE_28__ {TYPE_21__ vars; } ;
typedef  TYPE_13__ ngx_http_proxy_ctx_t ;
typedef  scalar_t__ in_port_t ;
struct TYPE_36__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_33__ {int /*<<< orphan*/  log; } ;
struct TYPE_32__ {int /*<<< orphan*/  elts; } ;
struct TYPE_30__ {int /*<<< orphan*/  elts; } ;
struct TYPE_29__ {int naddrs; scalar_t__ no_port; scalar_t__ port; int /*<<< orphan*/  host; int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_http_proxy_set_vars (TYPE_8__*,TYPE_21__*) ; 
 int /*<<< orphan*/ * ngx_http_script_run (TYPE_11__*,TYPE_9__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,TYPE_9__*,...) ; 
 int /*<<< orphan*/  ngx_memcpy (char*,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_8__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_8__*) ; 
 TYPE_14__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 char* ngx_pnalloc (int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ ngx_strncasecmp (scalar_t__,char*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_proxy_eval(ngx_http_request_t *r, ngx_http_proxy_ctx_t *ctx,
    ngx_http_proxy_loc_conf_t *plcf)
{
    u_char               *p;
    size_t                add;
    u_short               port;
    ngx_str_t             proxy;
    ngx_url_t             url;
    ngx_http_upstream_t  *u;

    if (ngx_http_script_run(r, &proxy, plcf->proxy_lengths->elts, 0,
                            plcf->proxy_values->elts)
        == NULL)
    {
        return NGX_ERROR;
    }

    if (proxy.len > 7
        && ngx_strncasecmp(proxy.data, (u_char *) "http://", 7) == 0)
    {
        add = 7;
        port = 80;

#if (NGX_HTTP_SSL)

    } else if (proxy.len > 8
               && ngx_strncasecmp(proxy.data, (u_char *) "https://", 8) == 0)
    {
        add = 8;
        port = 443;
        r->upstream->ssl = 1;

#endif

    } else {
        ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                      "invalid URL prefix in \"%V\"", &proxy);
        return NGX_ERROR;
    }

    u = r->upstream;

    u->schema.len = add;
    u->schema.data = proxy.data;

    ngx_memzero(&url, sizeof(ngx_url_t));

    url.url.len = proxy.len - add;
    url.url.data = proxy.data + add;
    url.default_port = port;
    url.uri_part = 1;
    url.no_resolve = 1;

    if (ngx_parse_url(r->pool, &url) != NGX_OK) {
        if (url.err) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "%s in upstream \"%V\"", url.err, &url.url);
        }

        return NGX_ERROR;
    }

    if (url.uri.len) {
        if (url.uri.data[0] == '?') {
            p = ngx_pnalloc(r->pool, url.uri.len + 1);
            if (p == NULL) {
                return NGX_ERROR;
            }

            *p++ = '/';
            ngx_memcpy(p, url.uri.data, url.uri.len);

            url.uri.len++;
            url.uri.data = p - 1;
        }
    }

    ctx->vars.key_start = u->schema;

    ngx_http_proxy_set_vars(&url, &ctx->vars);

    u->resolved = ngx_pcalloc(r->pool, sizeof(ngx_http_upstream_resolved_t));
    if (u->resolved == NULL) {
        return NGX_ERROR;
    }

    if (url.addrs) {
        u->resolved->sockaddr = url.addrs[0].sockaddr;
        u->resolved->socklen = url.addrs[0].socklen;
        u->resolved->name = url.addrs[0].name;
        u->resolved->naddrs = 1;
    }

    u->resolved->host = url.host;
    u->resolved->port = (in_port_t) (url.no_port ? port : url.port);
    u->resolved->no_port = url.no_port;

    return NGX_OK;
}