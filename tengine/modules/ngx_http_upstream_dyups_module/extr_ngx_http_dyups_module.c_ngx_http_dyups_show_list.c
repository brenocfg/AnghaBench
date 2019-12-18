#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_7__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_16__ {size_t len; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_17__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
struct TYPE_18__ {TYPE_2__* upstream; scalar_t__ deleted; int /*<<< orphan*/  dynamic; } ;
typedef  TYPE_5__ ngx_http_dyups_srv_conf_t ;
struct TYPE_14__ {size_t nelts; TYPE_5__* elts; } ;
struct TYPE_19__ {TYPE_1__ dy_upstreams; } ;
typedef  TYPE_6__ ngx_http_dyups_main_conf_t ;
struct TYPE_20__ {int /*<<< orphan*/  last; } ;
typedef  TYPE_7__ ngx_buf_t ;
struct TYPE_15__ {TYPE_3__ host; } ;

/* Variables and functions */
 TYPE_7__* ngx_create_temp_buf (int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 
 TYPE_6__* ngx_http_get_module_main_conf (TYPE_4__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_sprintf (int /*<<< orphan*/ ,char*,TYPE_3__*) ; 

__attribute__((used)) static ngx_buf_t *
ngx_http_dyups_show_list(ngx_http_request_t *r)
{
    ngx_uint_t                   i, len;
    ngx_str_t                    host;
    ngx_buf_t                   *buf;
    ngx_http_dyups_srv_conf_t   *duscfs, *duscf;
    ngx_http_dyups_main_conf_t  *dumcf;

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
    }

    return buf;
}