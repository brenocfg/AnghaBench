#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_9__ ;
typedef  struct TYPE_24__   TYPE_8__ ;
typedef  struct TYPE_23__   TYPE_7__ ;
typedef  struct TYPE_22__   TYPE_6__ ;
typedef  struct TYPE_21__   TYPE_5__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_21__ {size_t len; } ;
typedef  TYPE_5__ ngx_str_t ;
struct TYPE_22__ {int /*<<< orphan*/  down; int /*<<< orphan*/  backup; int /*<<< orphan*/  fail_timeout; int /*<<< orphan*/  max_fails; int /*<<< orphan*/  max_conns; int /*<<< orphan*/  weight; TYPE_4__* addrs; } ;
typedef  TYPE_6__ ngx_http_upstream_server_t ;
struct TYPE_23__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_24__ {TYPE_3__* upstream; scalar_t__ deleted; int /*<<< orphan*/  dynamic; } ;
typedef  TYPE_8__ ngx_http_dyups_srv_conf_t ;
struct TYPE_17__ {size_t nelts; TYPE_8__* elts; } ;
struct TYPE_25__ {TYPE_1__ dy_upstreams; } ;
typedef  TYPE_9__ ngx_http_dyups_main_conf_t ;
struct TYPE_16__ {void* last; } ;
typedef  TYPE_10__ ngx_buf_t ;
struct TYPE_20__ {int /*<<< orphan*/  name; } ;
struct TYPE_19__ {TYPE_2__* servers; TYPE_5__ host; } ;
struct TYPE_18__ {size_t nelts; TYPE_6__* elts; } ;

/* Variables and functions */
 TYPE_10__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 
 TYPE_9__* ngx_http_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 void* ngx_sprintf (void*,char*,...) ; 

__attribute__((used)) static ngx_buf_t *
ngx_http_dyups_show_detail(ngx_http_request_t *r)
{
    ngx_uint_t                   i, j, len;
    ngx_str_t                    host;
    ngx_buf_t                   *buf;
    ngx_http_dyups_srv_conf_t   *duscfs, *duscf;
    ngx_http_dyups_main_conf_t  *dumcf;
    ngx_http_upstream_server_t  *us;

    dumcf = ngx_http_get_module_main_conf(r, ngx_http_dyups_module);

    len = 0;
    duscfs = dumcf->dy_upstreams.elts;
    for (i = 0; i < dumcf->dy_upstreams.nelts; i++) {

        duscf = &duscfs[i];

        if (!duscf->dynamic) {
            continue;
        }

        if (duscf->deleted) {
            continue;
        }

        len += duscf->upstream->host.len + 1;

        for (j = 0; j < duscf->upstream->servers->nelts; j++) {
            len += sizeof("server ") + 256;
        }
    }

    buf = ngx_create_temp_buf(r->pool, len);
    if (buf == NULL) {
        return NULL;
    }

    for (i = 0; i < dumcf->dy_upstreams.nelts; i++) {

        duscf = &duscfs[i];

        if (!duscf->dynamic) {
            continue;
        }

        if (duscf->deleted) {
            continue;
        }

        host = duscf->upstream->host;
        buf->last = ngx_sprintf(buf->last, "%V\n", &host);

        us = duscf->upstream->servers->elts;
        for (j = 0; j < duscf->upstream->servers->nelts; j++) {
            buf->last = ngx_sprintf(buf->last,
                                    "server %V weight=%i "
#ifdef NGX_HTTP_UPSTREAM_MAX_CONNS
                                    "max_conns=%i "
#endif
                                    "max_fails=%i "
                                    "fail_timeout=%T backup=%d down=%d\n",
                                    &us[j].addrs->name,
                                    us[j].weight,
#ifdef NGX_HTTP_UPSTREAM_MAX_CONNS
                                    us[j].max_conns,
#endif
                                    us[j].max_fails,
                                    us[j].fail_timeout,
                                    us[j].backup,
                                    us[j].down);
        }
        buf->last = ngx_sprintf(buf->last, "\n");
    }

    return buf;
}