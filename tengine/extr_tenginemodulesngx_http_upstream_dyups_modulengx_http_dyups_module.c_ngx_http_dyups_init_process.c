#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_25__   TYPE_8__ ;
typedef  struct TYPE_24__   TYPE_7__ ;
typedef  struct TYPE_23__   TYPE_6__ ;
typedef  struct TYPE_22__   TYPE_4__ ;
typedef  struct TYPE_21__   TYPE_3__ ;
typedef  struct TYPE_20__   TYPE_2__ ;
typedef  struct TYPE_19__   TYPE_1__ ;
typedef  struct TYPE_18__   TYPE_16__ ;

/* Type definitions */
struct TYPE_19__ {int sec; scalar_t__ msec; } ;
typedef  TYPE_1__ ngx_time_t ;
struct TYPE_20__ {int /*<<< orphan*/  mutex; } ;
typedef  TYPE_2__ ngx_slab_pool_t ;
typedef  int /*<<< orphan*/  ngx_pid_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  size_t ngx_int_t ;
struct TYPE_21__ {int read_msg_timeout; int /*<<< orphan*/  conf_path; int /*<<< orphan*/  enable; } ;
typedef  TYPE_3__ ngx_http_dyups_main_conf_t ;
struct TYPE_22__ {scalar_t__ time; int /*<<< orphan*/  pid; TYPE_3__* data; int /*<<< orphan*/  log; int /*<<< orphan*/  handler; } ;
typedef  TYPE_4__ ngx_event_t ;
typedef  TYPE_4__ ngx_dyups_status_t ;
struct TYPE_23__ {scalar_t__ version; TYPE_4__* status; } ;
typedef  TYPE_6__ ngx_dyups_shctx_t ;
struct TYPE_24__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_7__ ngx_cycle_t ;
struct TYPE_25__ {int worker_processes; } ;
typedef  TYPE_8__ ngx_core_conf_t ;
struct TYPE_18__ {TYPE_6__* sh; TYPE_2__* shpool; TYPE_4__ msg_timer; } ;

/* Variables and functions */
 size_t NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 size_t NGX_OK ; 
 scalar_t__ NGX_PROCESS_HELPER ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_core_module ; 
 int /*<<< orphan*/  ngx_cycle ; 
 TYPE_16__ ngx_dyups_global_ctx ; 
 int /*<<< orphan*/  ngx_dyups_purge_msg (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 size_t ngx_dyups_restore_upstreams (TYPE_7__*,int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_3__* ngx_http_cycle_get_module_main_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_dyups_module ; 
 int /*<<< orphan*/  ngx_http_dyups_read_msg ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_4__*,int) ; 
 int /*<<< orphan*/  ngx_msleep (int) ; 
 int /*<<< orphan*/  ngx_pid ; 
 scalar_t__ ngx_process ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 
 TYPE_4__* ngx_slab_alloc_locked (TYPE_2__*,int) ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 TYPE_1__* ngx_timeofday () ; 

__attribute__((used)) static ngx_int_t
ngx_http_dyups_init_process(ngx_cycle_t *cycle)
{
    ngx_int_t                    rc, i;
    ngx_pid_t                    pid;
    ngx_time_t                  *tp;
    ngx_msec_t                   now;
    ngx_event_t                 *timer;
    ngx_core_conf_t             *ccf;
    ngx_slab_pool_t             *shpool;
    ngx_dyups_shctx_t           *sh;
    ngx_dyups_status_t          *status;
    ngx_http_dyups_main_conf_t  *dmcf;

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);

    dmcf = ngx_http_cycle_get_module_main_conf(ngx_cycle,
                                               ngx_http_dyups_module);

    if (!dmcf || !dmcf->enable || ngx_process == NGX_PROCESS_HELPER) {
        return NGX_OK;
    }

    timer = &ngx_dyups_global_ctx.msg_timer;
    ngx_memzero(timer, sizeof(ngx_event_t));

    timer->handler = ngx_http_dyups_read_msg;
    timer->log = cycle->log;
    timer->data = dmcf;

    ngx_add_timer(timer, dmcf->read_msg_timeout);

    shpool = ngx_dyups_global_ctx.shpool;
    sh = ngx_dyups_global_ctx.sh;

    ngx_shmtx_lock(&shpool->mutex);

    if (sh->status == NULL) {
        sh->status = ngx_slab_alloc_locked(shpool,
                           sizeof(ngx_dyups_status_t) * ccf->worker_processes);

        if (sh->status == NULL) {
            ngx_shmtx_unlock(&shpool->mutex);
            return NGX_ERROR;
        }

        ngx_memzero(sh->status,
                    sizeof(ngx_dyups_status_t) * ccf->worker_processes);

        ngx_shmtx_unlock(&shpool->mutex);
        return NGX_OK;
    }

    ngx_shmtx_unlock(&shpool->mutex);

    if (sh->version != 0) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                      "[dyups] process start after abnormal exits");

        ngx_msleep(dmcf->read_msg_timeout * 2);

        ngx_time_update();
        tp = ngx_timeofday();
        now = (ngx_msec_t) (tp->sec * 1000 + tp->msec);

        ngx_shmtx_lock(&shpool->mutex);

        if (sh->status == NULL) {
            ngx_shmtx_unlock(&shpool->mutex);
            return NGX_OK;
        }

        status = &sh->status[0];

        for (i = 1; i < ccf->worker_processes; i++) {

            ngx_log_error(NGX_LOG_WARN, cycle->log, 0,
                          "[dyups] process %P %ui %ui",
                          sh->status[i].pid, status->time, sh->status[i].time);

            if (status->time > sh->status[i].time) {
                status = &sh->status[i];
            }
        }

        pid = status->pid;
        status->time = now;
        status->pid = ngx_pid;

        ngx_log_error(NGX_LOG_WARN, cycle->log, 0,
                      "[dyups] new process is %P, old process is %P",
                      ngx_pid, pid);

        ngx_dyups_purge_msg(pid, ngx_pid);

        ngx_shmtx_unlock(&shpool->mutex);


        ngx_shmtx_lock(&shpool->mutex);

        rc = ngx_dyups_restore_upstreams(cycle, &dmcf->conf_path);

        ngx_shmtx_unlock(&shpool->mutex);

        if (rc != NGX_OK) {
            ngx_log_error(NGX_LOG_CRIT, cycle->log, 0,
                          "[dyups] process restore upstream failed");
        }
    }

    return NGX_OK;
}