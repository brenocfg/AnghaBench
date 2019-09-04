#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  intptr_t ngx_int_t ;
struct TYPE_10__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_cycle_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  NGX_PROCESS_WORKER ; 
 int /*<<< orphan*/  ngx_close_idle_connections (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_close_listening_sockets (TYPE_1__*) ; 
 scalar_t__ ngx_event_no_timers_left () ; 
 int ngx_exiting ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_process ; 
 int /*<<< orphan*/  ngx_process_events_and_timers (TYPE_1__*) ; 
 scalar_t__ ngx_quit ; 
 scalar_t__ ngx_reopen ; 
 int /*<<< orphan*/  ngx_reopen_files (TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_set_shutdown_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_setproctitle (char*) ; 
 scalar_t__ ngx_terminate ; 
 intptr_t ngx_worker ; 
 int /*<<< orphan*/  ngx_worker_process_exit (TYPE_1__*) ; 
 int /*<<< orphan*/  ngx_worker_process_init (TYPE_1__*,intptr_t) ; 

__attribute__((used)) static void
ngx_worker_process_cycle(ngx_cycle_t *cycle, void *data)
{
    ngx_int_t worker = (intptr_t) data;

    ngx_process = NGX_PROCESS_WORKER;
    ngx_worker = worker;

    ngx_worker_process_init(cycle, worker);

    ngx_setproctitle("worker process");

    for ( ;; ) {

        if (ngx_exiting) {
            if (ngx_event_no_timers_left() == NGX_OK) {
                ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "exiting");
                ngx_worker_process_exit(cycle);
            }
        }

        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, cycle->log, 0, "worker cycle");

        ngx_process_events_and_timers(cycle);

        if (ngx_terminate) {
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "exiting");
            ngx_worker_process_exit(cycle);
        }

        if (ngx_quit) {
            ngx_quit = 0;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0,
                          "gracefully shutting down");
            ngx_setproctitle("worker process is shutting down");

            if (!ngx_exiting) {
                ngx_exiting = 1;
                ngx_set_shutdown_timer(cycle);
                ngx_close_listening_sockets(cycle);
                ngx_close_idle_connections(cycle);
            }
        }

        if (ngx_reopen) {
            ngx_reopen = 0;
            ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0, "reopening logs");
            ngx_reopen_files(cycle, -1);
        }
    }
}