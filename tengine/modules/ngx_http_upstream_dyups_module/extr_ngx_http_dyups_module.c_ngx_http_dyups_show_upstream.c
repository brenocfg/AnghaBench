#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {TYPE_3__* addrs; } ;
typedef  TYPE_4__ ngx_http_upstream_server_t ;
struct TYPE_16__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_17__ {TYPE_2__* upstream; } ;
typedef  TYPE_6__ ngx_http_dyups_srv_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  last; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
struct TYPE_13__ {TYPE_1__* servers; } ;
struct TYPE_12__ {size_t nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 TYPE_7__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_buf_t *
ngx_http_dyups_show_upstream(ngx_http_request_t *r,
    ngx_http_dyups_srv_conf_t *duscf)
{
    ngx_uint_t                   i, len;
    ngx_buf_t                   *buf;
    ngx_http_upstream_server_t  *us;

    len = 0;
    for (i = 0; i < duscf->upstream->servers->nelts; i++) {
        len += sizeof("server ") + 81;
    }

    buf = ngx_create_temp_buf(r->pool, len);
    if (buf == NULL) {
        return NULL;
    }

    us = duscf->upstream->servers->elts;
    for (i = 0; i < duscf->upstream->servers->nelts; i++) {
        buf->last = ngx_sprintf(buf->last, "server %V\n",
                                &us[i].addrs->name);
    }

    return buf;
}