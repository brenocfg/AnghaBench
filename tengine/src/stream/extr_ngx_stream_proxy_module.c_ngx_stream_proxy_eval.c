#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
struct TYPE_16__ {int no_resolve; int /*<<< orphan*/  no_port; int /*<<< orphan*/  port; int /*<<< orphan*/  host; TYPE_2__* addrs; int /*<<< orphan*/  url; scalar_t__ err; } ;
typedef  TYPE_3__ ngx_url_t ;
struct TYPE_17__ {TYPE_10__* resolved; } ;
typedef  TYPE_4__ ngx_stream_upstream_t ;
typedef  int /*<<< orphan*/  ngx_stream_upstream_resolved_t ;
struct TYPE_18__ {TYPE_1__* connection; TYPE_4__* upstream; } ;
typedef  TYPE_5__ ngx_stream_session_t ;
struct TYPE_19__ {int /*<<< orphan*/  upstream_value; } ;
typedef  TYPE_6__ ngx_stream_proxy_srv_conf_t ;
typedef  int /*<<< orphan*/  ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_14__ {int /*<<< orphan*/  pool; int /*<<< orphan*/  log; } ;
struct TYPE_13__ {int naddrs; int /*<<< orphan*/  no_port; int /*<<< orphan*/  port; int /*<<< orphan*/  host; int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_3__*) ; 
 TYPE_10__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 scalar_t__ ngx_stream_complex_value (TYPE_5__*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_stream_proxy_eval(ngx_stream_session_t *s,
    ngx_stream_proxy_srv_conf_t *pscf)
{
    ngx_str_t               host;
    ngx_url_t               url;
    ngx_stream_upstream_t  *u;

    if (ngx_stream_complex_value(s, pscf->upstream_value, &host) != NGX_OK) {
        return NGX_ERROR;
    }

    ngx_memzero(&url, sizeof(ngx_url_t));

    url.url = host;
    url.no_resolve = 1;

    if (ngx_parse_url(s->connection->pool, &url) != NGX_OK) {
        if (url.err) {
            ngx_log_error(NGX_LOG_ERR, s->connection->log, 0,
                          "%s in upstream \"%V\"", url.err, &url.url);
        }

        return NGX_ERROR;
    }

    u = s->upstream;

    u->resolved = ngx_pcalloc(s->connection->pool,
                              sizeof(ngx_stream_upstream_resolved_t));
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
    u->resolved->port = url.port;
    u->resolved->no_port = url.no_port;

    return NGX_OK;
}