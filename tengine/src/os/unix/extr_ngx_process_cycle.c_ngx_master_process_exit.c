#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_9__ ;
typedef  struct TYPE_16__   TYPE_7__ ;
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
struct TYPE_14__ {int /*<<< orphan*/  pool; TYPE_1__** modules; int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_17__ {int /*<<< orphan*/  files_n; int /*<<< orphan*/  files; TYPE_5__* log; } ;
struct TYPE_16__ {int /*<<< orphan*/  fd; } ;
struct TYPE_15__ {int /*<<< orphan*/ * writer; int /*<<< orphan*/ * next; TYPE_7__* file; } ;
struct TYPE_13__ {int /*<<< orphan*/  (* exit_master ) (TYPE_2__*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  exit (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_close_listening_sockets (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_close_old_pipes () ; 
 TYPE_9__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_delete_pidfile (TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ ) ; 
 TYPE_9__ ngx_exit_cycle ; 
 TYPE_5__ ngx_exit_log ; 
 TYPE_7__ ngx_exit_log_file ; 
 int /*<<< orphan*/  ngx_increase_pipe_generation () ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 TYPE_5__* ngx_log_get_file_log (TYPE_5__*) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 

__attribute__((used)) static void
ngx_master_process_exit(ngx_cycle_t *cycle)
{
    ngx_uint_t  i;

    ngx_delete_pidfile(cycle);

    ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "exit");

    for (i = 0; cycle->modules[i]; i++) {
        if (cycle->modules[i]->exit_master) {
            cycle->modules[i]->exit_master(cycle);
        }
    }

    ngx_close_listening_sockets(cycle);

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
#if (T_PIPES)
    /* Terminate all pipe processes */

    ngx_increase_pipe_generation();
    ngx_close_old_pipes();
#endif

    exit(0);
}