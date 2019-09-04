#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_30__   TYPE_9__ ;
typedef  struct TYPE_29__   TYPE_8__ ;
typedef  struct TYPE_28__   TYPE_7__ ;
typedef  struct TYPE_27__   TYPE_6__ ;
typedef  struct TYPE_26__   TYPE_5__ ;
typedef  struct TYPE_25__   TYPE_4__ ;
typedef  struct TYPE_24__   TYPE_3__ ;
typedef  struct TYPE_23__   TYPE_2__ ;
typedef  struct TYPE_22__   TYPE_1__ ;
typedef  struct TYPE_21__   TYPE_11__ ;
typedef  struct TYPE_20__   TYPE_10__ ;

/* Type definitions */
struct TYPE_25__ {int /*<<< orphan*/  len; int /*<<< orphan*/  data; } ;
typedef  TYPE_4__ ngx_str_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_26__ {int valid; int /*<<< orphan*/  len; int /*<<< orphan*/  data; scalar_t__ not_found; } ;
typedef  TYPE_5__ ngx_http_variable_value_t ;
struct TYPE_27__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_6__ ngx_http_variable_t ;
struct TYPE_28__ {TYPE_5__* variables; TYPE_1__* connection; } ;
typedef  TYPE_7__ ngx_http_request_t ;
struct TYPE_23__ {TYPE_6__* elts; } ;
struct TYPE_29__ {TYPE_2__ variables; } ;
typedef  TYPE_8__ ngx_http_core_main_conf_t ;
struct TYPE_30__ {size_t index; int /*<<< orphan*/  (* set_handler ) (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ;int /*<<< orphan*/  value; } ;
typedef  TYPE_9__ ngx_http_auth_request_variable_t ;
struct TYPE_20__ {int /*<<< orphan*/  subrequest; } ;
typedef  TYPE_10__ ngx_http_auth_request_ctx_t ;
struct TYPE_21__ {TYPE_3__* vars; } ;
typedef  TYPE_11__ ngx_http_auth_request_conf_t ;
struct TYPE_24__ {int nelts; TYPE_9__* elts; } ;
struct TYPE_22__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ ngx_http_complex_value (int /*<<< orphan*/ ,int /*<<< orphan*/ *,TYPE_4__*) ; 
 int /*<<< orphan*/  ngx_http_core_module ; 
 TYPE_8__* ngx_http_get_module_main_conf (TYPE_7__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  stub1 (TYPE_7__*,TYPE_5__*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_auth_request_set_variables(ngx_http_request_t *r,
    ngx_http_auth_request_conf_t *arcf, ngx_http_auth_request_ctx_t *ctx)
{
    ngx_str_t                          val;
    ngx_http_variable_t               *v;
    ngx_http_variable_value_t         *vv;
    ngx_http_auth_request_variable_t  *av, *last;
    ngx_http_core_main_conf_t         *cmcf;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, r->connection->log, 0,
                   "auth request set variables");

    if (arcf->vars == NULL) {
        return NGX_OK;
    }

    cmcf = ngx_http_get_module_main_conf(r, ngx_http_core_module);
    v = cmcf->variables.elts;

    av = arcf->vars->elts;
    last = av + arcf->vars->nelts;

    while (av < last) {
        /*
         * explicitly set new value to make sure it will be available after
         * internal redirects
         */

        vv = &r->variables[av->index];

        if (ngx_http_complex_value(ctx->subrequest, &av->value, &val)
            != NGX_OK)
        {
            return NGX_ERROR;
        }

        vv->valid = 1;
        vv->not_found = 0;
        vv->data = val.data;
        vv->len = val.len;

        if (av->set_handler) {
            /*
             * set_handler only available in cmcf->variables_keys, so we store
             * it explicitly
             */

            av->set_handler(r, vv, v[av->index].data);
        }

        av++;
    }

    return NGX_OK;
}