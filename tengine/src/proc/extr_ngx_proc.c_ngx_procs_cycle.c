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
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_5__ ;
typedef  struct TYPE_21__   TYPE_4__ ;
typedef  struct TYPE_20__   TYPE_3__ ;
typedef  struct TYPE_19__   TYPE_2__ ;
typedef  struct TYPE_18__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_18__ {scalar_t__ data; } ;
struct TYPE_19__ {int /*<<< orphan*/  (* loop ) (TYPE_6__*) ;TYPE_1__ name; } ;
typedef  TYPE_2__ ngx_proc_module_t ;
struct TYPE_20__ {int /*<<< orphan*/  priority; int /*<<< orphan*/  delay_start; } ;
typedef  TYPE_3__ ngx_proc_conf_t ;
struct TYPE_21__ {TYPE_3__* proc_conf; TYPE_5__* module; } ;
typedef  TYPE_4__ ngx_proc_args_t ;
struct TYPE_22__ {TYPE_2__* ctx; } ;
typedef  TYPE_5__ ngx_module_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_23__ {scalar_t__ connection_n; int /*<<< orphan*/  log; TYPE_7__* connections; } ;
typedef  TYPE_6__ ngx_cycle_t ;
struct TYPE_24__ {int fd; int close; TYPE_9__* read; scalar_t__ idle; } ;
typedef  TYPE_7__ ngx_connection_t ;
struct TYPE_25__ {int /*<<< orphan*/  (* handler ) (TYPE_9__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  NGX_PROCESS_PROC ; 
 int /*<<< orphan*/  ngx_close_listening_sockets (TYPE_6__*) ; 
 int ngx_exiting ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_msleep (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_process ; 
 int /*<<< orphan*/  ngx_process_events_and_timers (TYPE_6__*) ; 
 int /*<<< orphan*/  ngx_procs_process_exit (TYPE_6__*,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_procs_process_init (TYPE_6__*,TYPE_2__*,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_quit ; 
 scalar_t__ ngx_reopen ; 
 int /*<<< orphan*/  ngx_reopen_files (TYPE_6__*,int) ; 
 int /*<<< orphan*/  ngx_setproctitle (char*) ; 
 scalar_t__ ngx_terminate ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 scalar_t__ ngx_use_accept_mutex ; 
 int /*<<< orphan*/  stub1 (TYPE_9__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_6__*) ; 

__attribute__((used)) static void
ngx_procs_cycle(ngx_cycle_t *cycle, void *data)
{
    ngx_int_t           rc;
    ngx_uint_t          i;
    ngx_module_t       *module;
    ngx_proc_args_t    *args;
    ngx_proc_conf_t    *cpcf;
    ngx_connection_t   *c;
    ngx_proc_module_t  *ctx;

    args = data;
    module = args->module;
    cpcf = args->proc_conf;
    ctx = module->ctx;
    ngx_process = NGX_PROCESS_PROC;

    ngx_setproctitle((char *) ctx->name.data);
    ngx_msleep(cpcf->delay_start);

    ngx_procs_process_init(cycle, ctx, cpcf->priority);
    ngx_close_listening_sockets(cycle);
    ngx_use_accept_mutex = 0;

    for ( ;; ) {
        if (ngx_exiting || ngx_quit) {
            ngx_exiting = 1;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0,
                          "process %V gracefully shutting down", &ctx->name);
            ngx_setproctitle("processes are shutting down");

            c = cycle->connections;

            for (i = 0; i < cycle->connection_n; i++) {
                if (c[i].fd != -1 && c[i].idle) {
                    c[i].close = 1;
                    c[i].read->handler(c[i].read);
                }
            }

            ngx_procs_process_exit(cycle, ctx);
        }

        if (ngx_terminate) {
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "process %V exiting",
                          &ctx->name);

            ngx_procs_process_exit(cycle, ctx);
        }

        if (ngx_reopen) {
            ngx_reopen = 0;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "reopening logs");
            ngx_reopen_files(cycle, -1);
        }

        if (ctx->loop) {
            rc = ctx->loop(cycle);
            if (rc != NGX_OK) {
                break;
            }
        }

        ngx_time_update();

        ngx_process_events_and_timers(cycle);
    }

    ngx_procs_process_exit(cycle, ctx);
}