#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_23__   TYPE_9__ ;
typedef  struct TYPE_22__   TYPE_8__ ;
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_6__ ;
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;

/* Type definitions */
struct TYPE_19__ {int no_resolve; int /*<<< orphan*/  no_port; int /*<<< orphan*/  port; int /*<<< orphan*/  host; TYPE_4__* addrs; int /*<<< orphan*/  url; scalar_t__ err; } ;
typedef  TYPE_5__ ngx_url_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_20__ {TYPE_9__* resolved; } ;
typedef  TYPE_6__ ngx_http_upstream_t ;
typedef  int /*<<< orphan*/  ngx_http_upstream_resolved_t ;
struct TYPE_21__ {TYPE_2__* scgi_values; TYPE_1__* scgi_lengths; } ;
typedef  TYPE_7__ ngx_http_scgi_loc_conf_t ;
struct TYPE_22__ {int /*<<< orphan*/  pool; TYPE_6__* upstream; TYPE_3__* connection; } ;
typedef  TYPE_8__ ngx_http_request_t ;
struct TYPE_23__ {int naddrs; int /*<<< orphan*/  no_port; int /*<<< orphan*/  port; int /*<<< orphan*/  host; int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_18__ {int /*<<< orphan*/  name; int /*<<< orphan*/  socklen; int /*<<< orphan*/  sockaddr; } ;
struct TYPE_17__ {int /*<<< orphan*/  log; } ;
struct TYPE_16__ {int /*<<< orphan*/  elts; } ;
struct TYPE_15__ {int /*<<< orphan*/  elts; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/ * ngx_http_script_run (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 scalar_t__ ngx_parse_url (int /*<<< orphan*/ ,TYPE_5__*) ; 
 TYPE_9__* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_scgi_eval(ngx_http_request_t *r, ngx_http_scgi_loc_conf_t * scf)
{
    ngx_url_t             url;
    ngx_http_upstream_t  *u;

    ngx_memzero(&url, sizeof(ngx_url_t));

    if (ngx_http_script_run(r, &url.url, scf->scgi_lengths->elts, 0,
                            scf->scgi_values->elts)
        == NULL)
    {
        return NGX_ERROR;
    }

    url.no_resolve = 1;

    if (ngx_parse_url(r->pool, &url) != NGX_OK) {
        if (url.err) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "%s in upstream \"%V\"", url.err, &url.url);
        }

        return NGX_ERROR;
    }

    u = r->upstream;

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
    u->resolved->port = url.port;
    u->resolved->no_port = url.no_port;

    return NGX_OK;
}