#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_9__ ;
typedef  struct TYPE_18__   TYPE_8__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_15__ {int /*<<< orphan*/  name; int /*<<< orphan*/  (* exit ) (TYPE_3__*) ;} ;
typedef  TYPE_2__ ngx_proc_module_t ;
struct TYPE_16__ {size_t connection_n; int /*<<< orphan*/  pool; int /*<<< orphan*/  log; TYPE_4__* connections; } ;
typedef  TYPE_3__ ngx_cycle_t ;
struct TYPE_17__ {int fd; TYPE_1__* read; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_19__ {TYPE_8__* file; } ;
struct TYPE_18__ {int /*<<< orphan*/  fd; } ;
struct TYPE_14__ {int /*<<< orphan*/  resolver; int /*<<< orphan*/  channel; int /*<<< orphan*/  accept; } ;
struct TYPE_13__ {TYPE_9__* log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_10__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_debug_point () ; 
 int ngx_debug_quit ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_exiting ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_9__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_10__ ngx_procs_exit_cycle ; 
 TYPE_9__ ngx_procs_exit_log ; 
 TYPE_8__ ngx_procs_exit_log_file ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_procs_process_exit(ngx_cycle_t *cycle, ngx_proc_module_t *module)
{
    ngx_uint_t         i;
    ngx_connection_t  *c;

    if (module->exit) {
        module->exit(cycle);
    }

    if (ngx_exiting) {
        c = cycle->connections;
        for (i = 0; i < cycle->connection_n; i++) {
            if (c[i].fd != -1
                && c[i].read
                && !c[i].read->accept
                && !c[i].read->channel
                && !c[i].read->resolver)
            {
                ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                              "open socket #%d left in connection %ui",
                              c[i].fd, i);
                ngx_debug_quit = 1;
            }
        }

        if (ngx_debug_quit) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, 0, "aborting");
            ngx_debug_point();
        }
    }

    /*
     * Copy ngx_cycle->log related data to the special static exit cycle,
     * log, and log file structures enough to allow a signal handler to log.
     * The handler may be called when standard ngx_cycle->log allocated from
     * ngx_cycle->pool is already destroyed.
     */

    ngx_procs_exit_log_file.fd = ngx_cycle->log->file->fd;

    ngx_procs_exit_log = *ngx_cycle->log;
    ngx_procs_exit_log.file = &ngx_procs_exit_log_file;

    ngx_procs_exit_cycle.log = &ngx_procs_exit_log;
    ngx_cycle = &ngx_procs_exit_cycle;

    ngx_log_error(NGX_LOG_NOTICE, ngx_cycle->log, 0, "process %V exit",
                  &module->name);

    ngx_destroy_pool(cycle->pool);

    exit(0);
}