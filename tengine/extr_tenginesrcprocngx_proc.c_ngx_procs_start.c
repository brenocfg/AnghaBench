#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_29__   TYPE_9__ ;
typedef  struct TYPE_28__   TYPE_8__ ;
typedef  struct TYPE_27__   TYPE_7__ ;
typedef  struct TYPE_26__   TYPE_6__ ;
typedef  struct TYPE_25__   TYPE_5__ ;
typedef  struct TYPE_24__   TYPE_4__ ;
typedef  struct TYPE_23__   TYPE_3__ ;
typedef  struct TYPE_22__   TYPE_2__ ;
typedef  struct TYPE_21__   TYPE_1__ ;
typedef  struct TYPE_20__   TYPE_18__ ;
typedef  struct TYPE_19__   TYPE_16__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_22__ {int /*<<< orphan*/  data; } ;
struct TYPE_24__ {int (* prepare ) (TYPE_8__*) ;TYPE_2__ name; } ;
typedef  TYPE_4__ ngx_proc_module_t ;
struct TYPE_21__ {int nelts; TYPE_6__** elts; } ;
struct TYPE_25__ {TYPE_1__ processes; } ;
typedef  TYPE_5__ ngx_proc_main_conf_t ;
struct TYPE_23__ {scalar_t__ data; } ;
struct TYPE_26__ {size_t count; TYPE_3__ name; scalar_t__ respawn; } ;
typedef  TYPE_6__ ngx_proc_conf_t ;
struct TYPE_27__ {TYPE_6__* proc_conf; TYPE_18__* module; } ;
typedef  TYPE_7__ ngx_proc_args_t ;
typedef  int ngx_int_t ;
struct TYPE_28__ {int /*<<< orphan*/  log; int /*<<< orphan*/  pool; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_8__ ngx_cycle_t ;
struct TYPE_29__ {size_t slot; int /*<<< orphan*/  fd; int /*<<< orphan*/  pid; int /*<<< orphan*/  command; } ;
typedef  TYPE_9__ ngx_channel_t ;
struct TYPE_20__ {scalar_t__ type; TYPE_4__* ctx; } ;
struct TYPE_19__ {int /*<<< orphan*/ * channel; int /*<<< orphan*/  pid; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_CMD_OPEN_CHANNEL ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int NGX_OK ; 
 int NGX_PROCESS_JUST_RESPAWN ; 
 int NGX_PROCESS_NORESPAWN ; 
 int NGX_PROCESS_RESPAWN ; 
 scalar_t__ NGX_PROC_MODULE ; 
 int /*<<< orphan*/ * ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_18__** ngx_modules ; 
 void* ngx_pcalloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_proc_core_module ; 
 TYPE_5__* ngx_proc_get_main_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_process_slot ; 
 TYPE_16__* ngx_processes ; 
 int /*<<< orphan*/  ngx_procs_cycle ; 
 int /*<<< orphan*/  ngx_procs_module ; 
 int /*<<< orphan*/  ngx_procs_pass_open_channel (TYPE_8__*,TYPE_9__*) ; 
 int /*<<< orphan*/  ngx_spawn_process (TYPE_8__*,int /*<<< orphan*/ ,TYPE_7__*,char*,int) ; 
 scalar_t__ ngx_strcmp (scalar_t__,int /*<<< orphan*/ ) ; 
 int stub1 (TYPE_8__*) ; 

ngx_int_t
ngx_procs_start(ngx_cycle_t *cycle, ngx_int_t type)
{
    ngx_int_t              rc, respawn;
    ngx_uint_t             i, p, n;
    ngx_channel_t          ch;
    ngx_proc_args_t      **args;
    ngx_proc_conf_t      **cpcfp;
    ngx_proc_module_t     *module;
    ngx_proc_main_conf_t  *cmcf;

    ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "start procs processes");

    if (ngx_get_conf(cycle->conf_ctx, ngx_procs_module) == NULL) {
        return NGX_OK;
    }

    ch.command = NGX_CMD_OPEN_CHANNEL;
    cmcf = ngx_proc_get_main_conf(cycle->conf_ctx, ngx_proc_core_module);

    cpcfp = cmcf->processes.elts;
    args = ngx_pcalloc(cycle->pool,
                       sizeof(ngx_proc_args_t *) * cmcf->processes.nelts);
    if (args == NULL) {
        return NGX_ERROR;
    }

    for (p = 0; p< cmcf->processes.nelts; p++) {
        args[p] = ngx_pcalloc(cycle->pool, sizeof(ngx_proc_args_t));
        if (args[p] == NULL) {
            return NGX_ERROR;
        }
    }

    respawn = type ? NGX_PROCESS_JUST_RESPAWN : NGX_PROCESS_RESPAWN;

    for (i = 0; ngx_modules[i]; i++) {

        if (ngx_modules[i]->type != NGX_PROC_MODULE) {
            continue;
        }

        module = ngx_modules[i]->ctx;

        for (p = 0; p < cmcf->processes.nelts; p++) {
            if (ngx_strcmp(cpcfp[p]->name.data, module->name.data) == 0) {

                if (module->prepare) {
                    rc = module->prepare(cycle);
                    if (rc != NGX_OK) {
                        break;
                    }
                }

                if (type == 1) {
                    if (cpcfp[p]->respawn) {
                        respawn = NGX_PROCESS_JUST_RESPAWN;
                    }
                } else {
                    if (cpcfp[p]->respawn) {
                        respawn = NGX_PROCESS_RESPAWN;
                    } else {
                        respawn = NGX_PROCESS_NORESPAWN;
                    }
                }

                /* processes count */
                for (n = 0; n < cpcfp[p]->count; n++) {
                    args[p]->module = ngx_modules[i];
                    args[p]->proc_conf = cpcfp[p];

                    ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0,
                                  "start process %V", &cpcfp[p]->name);

                    ngx_spawn_process(cycle, ngx_procs_cycle, args[p],
                                      (char *) cpcfp[p]->name.data, respawn);

                    ch.pid = ngx_processes[ngx_process_slot].pid;
                    ch.slot = ngx_process_slot;
                    ch.fd = ngx_processes[ngx_process_slot].channel[0];

                    ngx_procs_pass_open_channel(cycle, &ch);
                }
            }
        }
    }

    return NGX_OK;
}