#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_variable_value_t ;
struct TYPE_14__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_http_variable_t ;
struct TYPE_15__ {scalar_t__ uninitialized_variable_warn; } ;
typedef  TYPE_4__ ngx_http_rewrite_loc_conf_t ;
struct TYPE_16__ {TYPE_1__* connection; } ;
typedef  TYPE_5__ ngx_http_request_t ;
struct TYPE_13__ {TYPE_3__* elts; } ;
struct TYPE_17__ {TYPE_2__ variables; } ;
typedef  TYPE_6__ ngx_http_core_main_conf_t ;
struct TYPE_12__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_4__* ngx_http_get_module_loc_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 TYPE_6__* ngx_http_get_module_main_conf (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_rewrite_module ; 
 int /*<<< orphan*/  ngx_http_variable_null_value ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ngx_int_t
ngx_http_rewrite_var(ngx_http_request_t *r, ngx_http_variable_value_t *v,
    uintptr_t data)
{
    ngx_http_variable_t          *var;
    ngx_http_core_main_conf_t    *cmcf;
    ngx_http_rewrite_loc_conf_t  *rlcf;

    rlcf = ngx_http_get_module_loc_conf(r, ngx_http_rewrite_module);

    if (rlcf->uninitialized_variable_warn == 0) {
        *v = ngx_http_variable_null_value;
        return NGX_OK;
    }

    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);

    var = cmcf->variables.elts;

    /*
     * the ngx_http_rewrite_module sets variables directly in r->variables,
     * and they should be handled by ngx_http_get_indexed_variable(),
     * so the handler is called only if the variable is not initialized
     */

    ngx_log_error(NGX_LOG_WARN, r->connection->log, 0,
                  "using uninitialized \"%V\" variable", &var[data].name);

    *v = ngx_http_variable_null_value;

    return NGX_OK;
}