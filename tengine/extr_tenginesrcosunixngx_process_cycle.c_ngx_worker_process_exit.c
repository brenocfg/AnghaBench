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
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_12__ ;
typedef  struct TYPE_14__   TYPE_10__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_18__ {size_t connection_n; int /*<<< orphan*/  pool; TYPE_7__* log; TYPE_4__* connections; TYPE_1__** modules; } ;
typedef  TYPE_3__ ngx_cycle_t ;
struct TYPE_19__ {int fd; int /*<<< orphan*/  number; TYPE_2__* read; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_20__ {int /*<<< orphan*/ * writer; int /*<<< orphan*/ * next; TYPE_10__* file; } ;
struct TYPE_17__ {int /*<<< orphan*/  resolver; int /*<<< orphan*/  channel; int /*<<< orphan*/  accept; } ;
struct TYPE_16__ {int /*<<< orphan*/  (* exit_process ) (TYPE_3__*) ;} ;
struct TYPE_15__ {TYPE_7__* log; int /*<<< orphan*/  files_n; int /*<<< orphan*/  files; } ;
struct TYPE_14__ {int /*<<< orphan*/  fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 TYPE_12__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_debug_point () ; 
 int ngx_debug_quit ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ ) ; 
 TYPE_12__ ngx_exit_cycle ; 
 TYPE_7__ ngx_exit_log ; 
 TYPE_10__ ngx_exit_log_file ; 
 scalar_t__ ngx_exiting ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,TYPE_7__*,int /*<<< orphan*/ ,char*,...) ; 
 TYPE_7__* ngx_log_get_file_log (TYPE_7__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 

__attribute__((used)) static void
ngx_worker_process_exit(ngx_cycle_t *cycle)
{
    ngx_uint_t         i;
    ngx_connection_t  *c;

    for (i = 0; cycle->modules[i]; i++) {
        if (cycle->modules[i]->exit_process) {
            cycle->modules[i]->exit_process(cycle);
        }
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
                              "*%uA open socket #%d left in connection %ui",
                              c[i].number, c[i].fd, i);
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

    ngx_exit_log = *ngx_log_get_file_log(ngx_cycle->log);

    ngx_exit_log_file.fd = ngx_exit_log.file->fd;
    ngx_exit_log.file = &ngx_exit_log_file;
    ngx_exit_log.next = NULL;
    ngx_exit_log.writer = NULL;

    ngx_exit_cycle.log = &ngx_exit_log;
    ngx_exit_cycle.files = ngx_cycle->files;
    ngx_exit_cycle.files_n = ngx_cycle->files_n;
    ngx_cycle = &ngx_exit_cycle;

    ngx_destroy_pool(cycle->pool);

    ngx_log_error(NGX_LOG_NOTICE, ngx_cycle->log, 0, "exit");

    exit(0);
}