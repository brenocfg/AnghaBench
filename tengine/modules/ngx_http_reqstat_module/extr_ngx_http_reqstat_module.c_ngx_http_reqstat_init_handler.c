#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {TYPE_1__* variables; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_http_reqstat_store_t ;
struct TYPE_16__ {size_t index; } ;
typedef  TYPE_3__ ngx_http_reqstat_conf_t ;
struct TYPE_14__ {scalar_t__ valid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_DECLINED ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/ * ngx_http_get_indexed_variable (TYPE_2__*,size_t) ; 
 int /*<<< orphan*/ * ngx_http_get_module_ctx (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_loc_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_get_module_main_conf (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_http_reqstat_create_store (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/  ngx_http_reqstat_module ; 
 int /*<<< orphan*/  ngx_http_set_ctx (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_reqstat_init_handler(ngx_http_request_t *r)
{
    ngx_http_reqstat_conf_t      *rmcf, *rlcf;
    ngx_http_reqstat_store_t     *store;

    store = ngx_http_get_module_ctx(r, ngx_http_reqstat_module);
    rmcf = ngx_http_get_module_main_conf(r, ngx_http_reqstat_module);
    rlcf = ngx_http_get_module_loc_conf(r, ngx_http_reqstat_module);

    if (store == NULL) {
        if (r->variables[rmcf->index].valid) {
            return NGX_DECLINED;
        }

        store = ngx_http_reqstat_create_store(r, rlcf);
        if (store == NULL) {
            return NGX_ERROR;
        }

        ngx_http_set_ctx(r, store, ngx_http_reqstat_module);
    }

    if (ngx_http_get_indexed_variable(r, rmcf->index) == NULL) {
        return NGX_ERROR;
    }

    return NGX_DECLINED;
}