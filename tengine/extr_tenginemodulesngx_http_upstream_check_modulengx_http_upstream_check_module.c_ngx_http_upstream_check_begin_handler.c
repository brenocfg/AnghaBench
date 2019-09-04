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
typedef  struct TYPE_11__   TYPE_10__ ;

/* Type definitions */
typedef  int ngx_msec_t ;
struct TYPE_14__ {int check_interval; } ;
typedef  TYPE_3__ ngx_http_upstream_check_srv_conf_t ;
struct TYPE_15__ {scalar_t__ generation; } ;
typedef  TYPE_4__ ngx_http_upstream_check_peers_shm_t ;
struct TYPE_12__ {scalar_t__ timer_set; } ;
struct TYPE_16__ {TYPE_2__* shm; int /*<<< orphan*/  index; TYPE_1__ check_timeout_ev; TYPE_3__* conf; } ;
typedef  TYPE_5__ ngx_http_upstream_check_peer_t ;
struct TYPE_17__ {int /*<<< orphan*/  log; TYPE_5__* data; } ;
typedef  TYPE_6__ ngx_event_t ;
struct TYPE_13__ {scalar_t__ owner; void* access_time; int /*<<< orphan*/  mutex; } ;
struct TYPE_11__ {TYPE_4__* peers_shm; } ;

/* Variables and functions */
 scalar_t__ NGX_INVALID_PID ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 TYPE_10__* check_peers_ctx ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_6__*,int) ; 
 void* ngx_current_msec ; 
 int /*<<< orphan*/  ngx_http_upstream_check_connect_handler (TYPE_6__*) ; 
 scalar_t__ ngx_http_upstream_check_need_exit () ; 
 scalar_t__ ngx_http_upstream_check_shm_generation ; 
 int /*<<< orphan*/  ngx_log_debug5 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,scalar_t__,int,int) ; 
 scalar_t__ ngx_pid ; 
 int /*<<< orphan*/  ngx_shmtx_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_shmtx_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_upstream_check_begin_handler(ngx_event_t *event)
{
    ngx_msec_t                           interval;
    ngx_http_upstream_check_peer_t      *peer;
    ngx_http_upstream_check_srv_conf_t  *ucscf;
    ngx_http_upstream_check_peers_shm_t *peers_shm;

    if (ngx_http_upstream_check_need_exit()) {
        return;
    }

    if (check_peers_ctx == NULL) {
        return;
    }

    peers_shm = check_peers_ctx->peers_shm;
    peer = event->data;
    ucscf = peer->conf;

    ngx_add_timer(event, ucscf->check_interval / 2);

    /* This process is processing this peer now. */
    if (peer->shm->owner == ngx_pid ||
        peer->check_timeout_ev.timer_set) {
        return;
    }

    interval = ngx_current_msec - peer->shm->access_time;
    ngx_log_debug5(NGX_LOG_DEBUG_HTTP, event->log, 0,
                   "http check begin handler index: %ui, owner: %P, "
                   "ngx_pid: %P, interval: %M, check_interval: %M",
                   peer->index, peer->shm->owner,
                   ngx_pid, interval,
                   ucscf->check_interval);

    ngx_shmtx_lock(&peer->shm->mutex);

    if (peers_shm->generation != ngx_http_upstream_check_shm_generation) {
        ngx_shmtx_unlock(&peer->shm->mutex);
        return;
    }

    if ((interval >= ucscf->check_interval)
         && (peer->shm->owner == NGX_INVALID_PID)) {

        peer->shm->owner = ngx_pid;

    } else if (interval >= (ucscf->check_interval << 4)) {

        /*
         * If the check peer has been untouched for 2^4 times of
         * the check interval, activate the current timer.
         * Sometimes, the checking process may disappear
         * under some abnormal circumstances, and the clean event
         * will never be triggered.
         */
        peer->shm->owner = ngx_pid;
        peer->shm->access_time = ngx_current_msec;
    }

    ngx_shmtx_unlock(&peer->shm->mutex);

    if (peer->shm->owner == ngx_pid) {
        ngx_http_upstream_check_connect_handler(event);
    }
}