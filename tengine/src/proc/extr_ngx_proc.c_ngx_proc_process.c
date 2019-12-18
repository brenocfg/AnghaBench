#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_27__   TYPE_8__ ;
typedef  struct TYPE_26__   TYPE_7__ ;
typedef  struct TYPE_25__   TYPE_6__ ;
typedef  struct TYPE_24__   TYPE_5__ ;
typedef  struct TYPE_23__   TYPE_4__ ;
typedef  struct TYPE_22__   TYPE_3__ ;
typedef  struct TYPE_21__   TYPE_2__ ;
typedef  struct TYPE_20__   TYPE_1__ ;
typedef  struct TYPE_19__   TYPE_16__ ;
typedef  struct TYPE_18__   TYPE_12__ ;
typedef  struct TYPE_17__   TYPE_11__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
typedef  TYPE_3__ ngx_str_t ;
struct TYPE_21__ {int /*<<< orphan*/  data; } ;
struct TYPE_23__ {void* (* create_proc_conf ) (TYPE_8__*) ;TYPE_2__ name; } ;
typedef  TYPE_4__ ngx_proc_module_t ;
struct TYPE_19__ {size_t nelts; TYPE_6__** elts; } ;
struct TYPE_24__ {TYPE_16__ processes; } ;
typedef  TYPE_5__ ngx_proc_main_conf_t ;
struct TYPE_25__ {TYPE_3__ name; TYPE_7__* ctx; } ;
typedef  TYPE_6__ ngx_proc_conf_t ;
struct TYPE_26__ {TYPE_5__** main_conf; TYPE_6__** proc_conf; } ;
typedef  TYPE_7__ ngx_proc_conf_ctx_t ;
typedef  size_t ngx_int_t ;
typedef  int ngx_flag_t ;
struct TYPE_27__ {int /*<<< orphan*/  cmd_type; TYPE_7__* ctx; int /*<<< orphan*/  pool; TYPE_1__* args; } ;
typedef  TYPE_8__ ngx_conf_t ;
typedef  int /*<<< orphan*/  ngx_command_t ;
struct TYPE_20__ {TYPE_3__* elts; } ;
struct TYPE_18__ {scalar_t__ type; size_t ctx_index; TYPE_4__* ctx; } ;
struct TYPE_17__ {size_t ctx_index; } ;

/* Variables and functions */
 char* NGX_CONF_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  NGX_PROC_CONF ; 
 scalar_t__ NGX_PROC_MODULE ; 
 TYPE_6__** ngx_array_push (TYPE_16__*) ; 
 int /*<<< orphan*/  ngx_conf_log_error (int /*<<< orphan*/ ,TYPE_8__*,int /*<<< orphan*/ ,char*,...) ; 
 char* ngx_conf_parse (TYPE_8__*,int /*<<< orphan*/ *) ; 
 TYPE_12__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 TYPE_11__ ngx_proc_core_module ; 
 int ngx_procs_max_module ; 
 scalar_t__ ngx_strcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 void* stub1 (TYPE_8__*) ; 

__attribute__((used)) static char *
ngx_proc_process(ngx_conf_t *cf, ngx_command_t *cmd, void *conf)
{
    char                  *rv;
    void                  *mconf;
    ngx_int_t              i;
    ngx_str_t             *value;
    ngx_flag_t             flag;
    ngx_conf_t             pcf;
    ngx_uint_t             m;
    ngx_proc_conf_t       *cpcf, **cpcfp;
    ngx_proc_module_t     *module;
    ngx_proc_conf_ctx_t   *ctx, *procs_ctx;
    ngx_proc_main_conf_t  *cmcf;

    value = cf->args->elts;
    flag = 0;

    for (m = 0; ngx_modules[m]; m++) {
        if (ngx_modules[m]->type != NGX_PROC_MODULE) {
            continue;
        }
        module = ngx_modules[m]->ctx;

        if (ngx_strcmp(module->name.data, value[1].data) == 0) {
            flag = 1;
            break;
        }
    }

    if (flag == 0) {
        ngx_conf_log_error(NGX_LOG_EMERG, cf, 0,
                           "no %V process module", &value[1]);
        return NGX_CONF_ERROR;
    }

    /* new conf ctx */
    ctx = ngx_pcalloc(cf->pool, sizeof(ngx_proc_conf_ctx_t));
    if (ctx == NULL) {
        return NGX_CONF_ERROR;
    }

    procs_ctx = cf->ctx;
    ctx->main_conf = procs_ctx->main_conf; /* old main conf */

    /* the processes{}'s proc_conf */

    ctx->proc_conf = ngx_pcalloc(cf->pool,
                                 sizeof(void *) * ngx_procs_max_module);
    if (ctx->proc_conf == NULL) {
        return NGX_CONF_ERROR;
    }

    for (m = 0; ngx_modules[m]; m++) {
        if (ngx_modules[m]->type != NGX_PROC_MODULE) {
            continue;
        }

        module = ngx_modules[m]->ctx;

        if (module->create_proc_conf) {
            mconf = module->create_proc_conf(cf);

            if (mconf == NULL) {
                return NGX_CONF_ERROR;
            }

            /* new proc conf */
            ctx->proc_conf[ngx_modules[m]->ctx_index] = mconf;
        }
    }

    /* the proc configuration context */

    cpcf = ctx->proc_conf[ngx_proc_core_module.ctx_index];
    cpcf->ctx = ctx;
    cpcf->name = value[1];

    cmcf = ctx->main_conf[ngx_proc_core_module.ctx_index];

    cpcfp = ngx_array_push(&cmcf->processes);
    if (cpcfp == NULL) {
        return NGX_CONF_ERROR;
    }

    *cpcfp = cpcf;

    /* check process conf repeat */
    cpcfp = cmcf->processes.elts;
    for (i = cmcf->processes.nelts - 2; i >= 0 ; i--) {
        if (ngx_strcmp(cpcfp[i]->name.data, cpcf->name.data) == 0) {
            ngx_conf_log_error(NGX_LOG_EMERG, cf, 0, "process repeat");
            return NGX_CONF_ERROR;
        }
    }

    /* parse inside process{} */

    pcf = *cf;
    cf->ctx = ctx;
    cf->cmd_type = NGX_PROC_CONF;

    rv = ngx_conf_parse(cf, NULL);

    *cf = pcf;

    return rv;
}