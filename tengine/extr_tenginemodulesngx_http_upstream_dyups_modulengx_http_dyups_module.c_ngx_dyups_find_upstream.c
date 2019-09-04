#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
typedef  int ngx_int_t ;
struct TYPE_13__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_15__ {TYPE_2__ host; } ;
typedef  TYPE_4__ ngx_http_upstream_srv_conf_t ;
struct TYPE_16__ {scalar_t__ deleted; scalar_t__* ref; TYPE_4__* upstream; int /*<<< orphan*/ * pool; int /*<<< orphan*/  idx; int /*<<< orphan*/  dynamic; } ;
typedef  TYPE_5__ ngx_http_dyups_srv_conf_t ;
struct TYPE_12__ {size_t nelts; TYPE_5__* elts; } ;
struct TYPE_17__ {TYPE_1__ dy_upstreams; } ;
typedef  TYPE_6__ ngx_http_dyups_main_conf_t ;
struct TYPE_18__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_DYUPS_DELETED ; 
 scalar_t__ NGX_DYUPS_DELETING ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 TYPE_8__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 TYPE_6__* ngx_http_cycle_get_module_main_conf (TYPE_8__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,...) ; 
 scalar_t__ ngx_strncasecmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static ngx_http_dyups_srv_conf_t *
ngx_dyups_find_upstream(ngx_str_t *name, ngx_int_t *idx)
{
    ngx_uint_t                      i;
    ngx_http_dyups_srv_conf_t      *duscfs, *duscf, *duscf_del;
    ngx_http_dyups_main_conf_t     *dumcf;
    ngx_http_upstream_srv_conf_t   *uscf;

    dumcf = ngx_http_cycle_get_module_main_conf(ngx_cycle,
                                                ngx_http_dyups_module);
    *idx = -1;
    duscf_del = NULL;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "[dyups] find dynamic upstream");

    duscfs = dumcf->dy_upstreams.elts;
    for (i = 0; i < dumcf->dy_upstreams.nelts; i++) {

        duscf = &duscfs[i];
        if (!duscf->dynamic) {
            continue;
        }

        if (duscf->deleted == NGX_DYUPS_DELETING) {

            ngx_log_error(NGX_LOG_DEBUG, ngx_cycle->log, 0,
                          "[dyups] find upstream idx: %ui ref: %ui "
                          "on %V deleting",
                          i, *(duscf->ref), &duscf->upstream->host);

            if (*(duscf->ref) == 0) {
                ngx_log_error(NGX_LOG_INFO, ngx_cycle->log, 0,
                              "[dyups] free dynamic upstream in find upstream"
                              " %ui", duscf->idx);

                duscf->deleted = NGX_DYUPS_DELETED;

                if (duscf->pool) {
                    ngx_destroy_pool(duscf->pool);
                    duscf->pool = NULL;
                }
            }
        }

        if (duscf->deleted == NGX_DYUPS_DELETING) {
            continue;
        }

        if (duscf->deleted == NGX_DYUPS_DELETED) {
            *idx = i;
            duscf_del = duscf;
            continue;
        }

        uscf = duscf->upstream;

        if (uscf->host.len != name->len
            || ngx_strncasecmp(uscf->host.data, name->data, uscf->host.len)
               != 0)
        {
            continue;
        }

        *idx = i;

        return duscf;
    }

    return duscf_del;
}