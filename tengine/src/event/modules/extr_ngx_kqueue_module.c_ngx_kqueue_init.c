#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct timespec {scalar_t__ tv_nsec; scalar_t__ tv_sec; } ;
struct kevent {int flags; scalar_t__ udata; scalar_t__ data; scalar_t__ fflags; int /*<<< orphan*/  filter; scalar_t__ ident; } ;
typedef  scalar_t__ ngx_msec_t ;
struct TYPE_6__ {int changes; int events; } ;
typedef  TYPE_1__ ngx_kqueue_conf_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_7__ {int /*<<< orphan*/  log; int /*<<< orphan*/  conf_ctx; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_8__ {int /*<<< orphan*/  actions; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVFILT_TIMER ; 
 int EV_ADD ; 
 int EV_ENABLE ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 scalar_t__ NGX_OK ; 
 int NGX_USE_CLEAR_EVENT ; 
 int NGX_USE_KQUEUE_EVENT ; 
 int NGX_USE_LEVEL_EVENT ; 
 int NGX_USE_LOWAT_EVENT ; 
 int NGX_USE_ONESHOT_EVENT ; 
 int NGX_USE_TIMER_EVENT ; 
 int NGX_USE_VNODE_EVENT ; 
 struct kevent* change_list ; 
 struct kevent* event_list ; 
 int kevent (int,struct kevent*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ,struct timespec*) ; 
 int kqueue () ; 
 int max_changes ; 
 scalar_t__ nchanges ; 
 int nevents ; 
 struct kevent* ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_errno ; 
 int /*<<< orphan*/  ngx_event_actions ; 
 int ngx_event_flags ; 
 TYPE_1__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_free (struct kevent*) ; 
 int /*<<< orphan*/  ngx_io ; 
 int ngx_kqueue ; 
 int /*<<< orphan*/  ngx_kqueue_module ; 
 TYPE_3__ ngx_kqueue_module_ctx ; 
 scalar_t__ ngx_kqueue_notify_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_os_io ; 

__attribute__((used)) static ngx_int_t
ngx_kqueue_init(ngx_cycle_t *cycle, ngx_msec_t timer)
{
    ngx_kqueue_conf_t  *kcf;
    struct timespec     ts;
#if (NGX_HAVE_TIMER_EVENT)
    struct kevent       kev;
#endif

    kcf = ngx_event_get_conf(cycle->conf_ctx, ngx_kqueue_module);

    if (ngx_kqueue == -1) {
        ngx_kqueue = kqueue();

        if (ngx_kqueue == -1) {
            ngx_log_error(NGX_LOG_EMERG, cycle->log, ngx_errno,
                          "kqueue() failed");
            return NGX_ERROR;
        }

#ifdef EVFILT_USER
        if (ngx_kqueue_notify_init(cycle->log) != NGX_OK) {
            return NGX_ERROR;
        }
#endif
    }

    if (max_changes < kcf->changes) {
        if (nchanges) {
            ts.tv_sec = 0;
            ts.tv_nsec = 0;

            if (kevent(ngx_kqueue, change_list, (int) nchanges, NULL, 0, &ts)
                == -1)
            {
                ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                              "kevent() failed");
                return NGX_ERROR;
            }
            nchanges = 0;
        }

        if (change_list) {
            ngx_free(change_list);
        }

        change_list = ngx_alloc(kcf->changes * sizeof(struct kevent),
                                cycle->log);
        if (change_list == NULL) {
            return NGX_ERROR;
        }
    }

    max_changes = kcf->changes;

    if (nevents < kcf->events) {
        if (event_list) {
            ngx_free(event_list);
        }

        event_list = ngx_alloc(kcf->events * sizeof(struct kevent), cycle->log);
        if (event_list == NULL) {
            return NGX_ERROR;
        }
    }

    ngx_event_flags = NGX_USE_ONESHOT_EVENT
                      |NGX_USE_KQUEUE_EVENT
                      |NGX_USE_VNODE_EVENT;

#if (NGX_HAVE_TIMER_EVENT)

    if (timer) {
        kev.ident = 0;
        kev.filter = EVFILT_TIMER;
        kev.flags = EV_ADD|EV_ENABLE;
        kev.fflags = 0;
        kev.data = timer;
        kev.udata = 0;

        ts.tv_sec = 0;
        ts.tv_nsec = 0;

        if (kevent(ngx_kqueue, &kev, 1, NULL, 0, &ts) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "kevent(EVFILT_TIMER) failed");
            return NGX_ERROR;
        }

        ngx_event_flags |= NGX_USE_TIMER_EVENT;
    }

#endif

#if (NGX_HAVE_CLEAR_EVENT)
    ngx_event_flags |= NGX_USE_CLEAR_EVENT;
#else
    ngx_event_flags |= NGX_USE_LEVEL_EVENT;
#endif

#if (NGX_HAVE_LOWAT_EVENT)
    ngx_event_flags |= NGX_USE_LOWAT_EVENT;
#endif

    nevents = kcf->events;

    ngx_io = ngx_os_io;

    ngx_event_actions = ngx_kqueue_module_ctx.actions;

    return NGX_OK;
}