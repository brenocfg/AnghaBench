#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_8__ ;
typedef  struct TYPE_19__   TYPE_6__ ;
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;
typedef  struct TYPE_13__   TYPE_11__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct rlimit {scalar_t__ rlim_cur; } ;
typedef  scalar_t__ ngx_uint_t ;
struct TYPE_15__ {int msec; } ;
typedef  TYPE_2__ ngx_time_t ;
typedef  int /*<<< orphan*/  ngx_shmtx_sh_t ;
struct TYPE_16__ {size_t size; int /*<<< orphan*/ * addr; int /*<<< orphan*/  log; int /*<<< orphan*/  name; } ;
typedef  TYPE_3__ ngx_shm_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_17__ {scalar_t__ connections; int /*<<< orphan*/  name; } ;
typedef  TYPE_4__ ngx_event_conf_t ;
struct TYPE_14__ {int /*<<< orphan*/  data; } ;
struct TYPE_18__ {int /*<<< orphan*/  log; TYPE_1__ lock_file; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_5__ ngx_cycle_t ;
struct TYPE_19__ {scalar_t__ rlimit_nofile; scalar_t__ master; int /*<<< orphan*/  timer_resolution; } ;
typedef  TYPE_6__ ngx_core_conf_t ;
typedef  int /*<<< orphan*/  ngx_atomic_t ;
struct TYPE_20__ {scalar_t__ spin; } ;
struct TYPE_13__ {size_t ctx_index; } ;

/* Variables and functions */
 scalar_t__ NGX_CONF_UNSET ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_NOTICE ; 
 int /*<<< orphan*/  NGX_LOG_WARN ; 
 scalar_t__ NGX_OK ; 
 scalar_t__ NGX_PROCESS_MASTER ; 
 int /*<<< orphan*/  RLIMIT_NOFILE ; 
 int getrlimit (int /*<<< orphan*/ ,struct rlimit*) ; 
 TYPE_8__ ngx_accept_mutex ; 
 int /*<<< orphan*/ * ngx_accept_mutex_ptr ; 
 int /*<<< orphan*/  ngx_atomic_cmp_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * ngx_connection_counter ; 
 int /*<<< orphan*/  ngx_core_module ; 
 int /*<<< orphan*/  ngx_errno ; 
 TYPE_11__ ngx_event_core_module ; 
 int /*<<< orphan*/  ngx_events_module ; 
 void*** ngx_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,...) ; 
 scalar_t__ ngx_pid ; 
 scalar_t__ ngx_process ; 
 scalar_t__ ngx_random_number ; 
 scalar_t__ ngx_shm_alloc (TYPE_3__*) ; 
 scalar_t__ ngx_shmtx_create (TYPE_8__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_stat_accepted ; 
 int /*<<< orphan*/ * ngx_stat_active ; 
 int /*<<< orphan*/ * ngx_stat_handled ; 
 int /*<<< orphan*/ * ngx_stat_reading ; 
 int /*<<< orphan*/ * ngx_stat_request_time ; 
 int /*<<< orphan*/ * ngx_stat_requests ; 
 int /*<<< orphan*/ * ngx_stat_waiting ; 
 int /*<<< orphan*/ * ngx_stat_writing ; 
 int /*<<< orphan*/  ngx_str_set (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * ngx_temp_number ; 
 int /*<<< orphan*/  ngx_test_config ; 
 TYPE_2__* ngx_timeofday () ; 
 int /*<<< orphan*/  ngx_timer_resolution ; 

__attribute__((used)) static ngx_int_t
ngx_event_module_init(ngx_cycle_t *cycle)
{
    void              ***cf;
    u_char              *shared;
    size_t               size, cl;
    ngx_shm_t            shm;
    ngx_time_t          *tp;
    ngx_core_conf_t     *ccf;
    ngx_event_conf_t    *ecf;

    cf = ngx_get_conf(cycle->conf_ctx, ngx_events_module);
    ecf = (*cf)[ngx_event_core_module.ctx_index];

    if (!ngx_test_config && ngx_process <= NGX_PROCESS_MASTER) {
        ngx_log_error(NGX_LOG_NOTICE, cycle->log, 0,
                      "using the \"%s\" event method", ecf->name);
    }

    ccf = (ngx_core_conf_t *) ngx_get_conf(cycle->conf_ctx, ngx_core_module);

    ngx_timer_resolution = ccf->timer_resolution;

#if !(NGX_WIN32)
    {
    ngx_int_t      limit;
    struct rlimit  rlmt;

    if (getrlimit(RLIMIT_NOFILE, &rlmt) == -1) {
        ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                      "getrlimit(RLIMIT_NOFILE) failed, ignored");

    } else {
        if (ecf->connections > (ngx_uint_t) rlmt.rlim_cur
            && (ccf->rlimit_nofile == NGX_CONF_UNSET
                || ecf->connections > (ngx_uint_t) ccf->rlimit_nofile))
        {
            limit = (ccf->rlimit_nofile == NGX_CONF_UNSET) ?
                         (ngx_int_t) rlmt.rlim_cur : ccf->rlimit_nofile;

            ngx_log_error(NGX_LOG_WARN, cycle->log, 0,
                          "%ui worker_connections exceed "
                          "open file resource limit: %i",
                          ecf->connections, limit);
        }
    }
    }
#endif /* !(NGX_WIN32) */


    if (ccf->master == 0) {
        return NGX_OK;
    }

    if (ngx_accept_mutex_ptr) {
        return NGX_OK;
    }


    /* cl should be equal to or greater than cache line size */

    cl = 128;

    size = cl            /* ngx_accept_mutex */
           + cl          /* ngx_connection_counter */
           + cl;         /* ngx_temp_number */

#if (NGX_STAT_STUB)

    size += cl           /* ngx_stat_accepted */
           + cl          /* ngx_stat_handled */
           + cl          /* ngx_stat_requests */
           + cl          /* ngx_stat_active */
           + cl          /* ngx_stat_reading */
           + cl          /* ngx_stat_writing */
           + cl          /* ngx_stat_waiting */
#if (T_NGX_HTTP_STUB_STATUS)
           + cl         /* ngx_stat_request_time */
#endif
           ;

#endif

    shm.size = size;
    ngx_str_set(&shm.name, "nginx_shared_zone");
    shm.log = cycle->log;

    if (ngx_shm_alloc(&shm) != NGX_OK) {
        return NGX_ERROR;
    }

    shared = shm.addr;

    ngx_accept_mutex_ptr = (ngx_atomic_t *) shared;
    ngx_accept_mutex.spin = (ngx_uint_t) -1;

    if (ngx_shmtx_create(&ngx_accept_mutex, (ngx_shmtx_sh_t *) shared,
                         cycle->lock_file.data)
        != NGX_OK)
    {
        return NGX_ERROR;
    }

    ngx_connection_counter = (ngx_atomic_t *) (shared + 1 * cl);

    (void) ngx_atomic_cmp_set(ngx_connection_counter, 0, 1);

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "counter: %p, %uA",
                   ngx_connection_counter, *ngx_connection_counter);

    ngx_temp_number = (ngx_atomic_t *) (shared + 2 * cl);

    tp = ngx_timeofday();

    ngx_random_number = (tp->msec << 16) + ngx_pid;

#if (NGX_STAT_STUB)

    ngx_stat_accepted = (ngx_atomic_t *) (shared + 3 * cl);
    ngx_stat_handled = (ngx_atomic_t *) (shared + 4 * cl);
    ngx_stat_requests = (ngx_atomic_t *) (shared + 5 * cl);
    ngx_stat_active = (ngx_atomic_t *) (shared + 6 * cl);
    ngx_stat_reading = (ngx_atomic_t *) (shared + 7 * cl);
    ngx_stat_writing = (ngx_atomic_t *) (shared + 8 * cl);
    ngx_stat_waiting = (ngx_atomic_t *) (shared + 9 * cl);

#if (T_NGX_HTTP_STUB_STATUS)
    ngx_stat_request_time = (ngx_atomic_t *) (shared + 10 * cl);
#endif

#endif

    return NGX_OK;
}