#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_20__   TYPE_5__ ;
typedef  struct TYPE_19__   TYPE_4__ ;
typedef  struct TYPE_18__   TYPE_3__ ;
typedef  struct TYPE_17__   TYPE_2__ ;
typedef  struct TYPE_16__   TYPE_1__ ;
typedef  struct TYPE_15__   TYPE_13__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
struct timespec {int tv_sec; int tv_nsec; } ;
struct sigaction {int /*<<< orphan*/  sa_mask; int /*<<< orphan*/  sa_handler; } ;
struct TYPE_16__ {size_t si_fd; int si_band; } ;
typedef  TYPE_1__ siginfo_t ;
typedef  int ngx_uint_t ;
struct TYPE_17__ {int signo; } ;
typedef  TYPE_2__ ngx_rtsig_conf_t ;
typedef  int /*<<< orphan*/  ngx_queue_t ;
typedef  int ngx_msec_t ;
typedef  int ngx_int_t ;
struct TYPE_18__ {int instance; int ready; int /*<<< orphan*/  (* handler ) (TYPE_3__*) ;scalar_t__ active; scalar_t__ accept; } ;
typedef  TYPE_3__ ngx_event_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_4__ ngx_cycle_t ;
struct TYPE_20__ {TYPE_3__* write; TYPE_3__* read; } ;
typedef  TYPE_5__ ngx_connection_t ;
struct TYPE_15__ {TYPE_5__** files; int /*<<< orphan*/  conf_ctx; } ;
struct TYPE_14__ {int /*<<< orphan*/  process_events; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
 scalar_t__ NGX_EAGAIN ; 
 scalar_t__ NGX_EINTR ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 int NGX_OK ; 
 int NGX_POST_EVENTS ; 
 int NGX_TIMER_INFINITE ; 
 int NGX_UPDATE_TIME ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLOUT ; 
 int SIGALRM ; 
 int SIGIO ; 
 int /*<<< orphan*/  SIG_DFL ; 
 TYPE_13__* ngx_cycle ; 
 scalar_t__ ngx_errno ; 
 TYPE_12__ ngx_event_actions ; 
 TYPE_2__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (struct sigaction*,int) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_accept_events ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_rtsig_module ; 
 int /*<<< orphan*/  ngx_rtsig_process_overflow ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 int overflow ; 
 int overflow_current ; 
 int /*<<< orphan*/  set ; 
 int sigaction (int,struct sigaction*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sigemptyset (int /*<<< orphan*/ *) ; 
 int sigtimedwait (int /*<<< orphan*/ *,TYPE_1__*,struct timespec*) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*) ; 

__attribute__((used)) static ngx_int_t
ngx_rtsig_process_events(ngx_cycle_t *cycle, ngx_msec_t timer, ngx_uint_t flags)
{
    int                 signo;
    ngx_int_t           instance;
    ngx_err_t           err;
    siginfo_t           si;
    ngx_event_t        *rev, *wev;
    ngx_queue_t        *queue;
    struct timespec     ts, *tp;
    struct sigaction    sa;
    ngx_connection_t   *c;
    ngx_rtsig_conf_t   *rtscf;

    if (timer == NGX_TIMER_INFINITE) {
        tp = NULL;

    } else {
        ts.tv_sec = timer / 1000;
        ts.tv_nsec = (timer % 1000) * 1000000;
        tp = &ts;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "rtsig timer: %M", timer);

    /* Linux's sigwaitinfo() is sigtimedwait() with the NULL timeout pointer */

    signo = sigtimedwait(&set, &si, tp);

    if (signo == -1) {
        err = ngx_errno;

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, err,
                       "rtsig signo:%d", signo);

        if (flags & NGX_UPDATE_TIME) {
            ngx_time_update();
        }

        if (err == NGX_EAGAIN) {

            /* timeout */

            if (timer != NGX_TIMER_INFINITE) {
                return NGX_AGAIN;
            }

            ngx_log_error(NGX_LOG_ALERT, cycle->log, err,
                          "sigtimedwait() returned EAGAIN without timeout");
            return NGX_ERROR;
        }

        ngx_log_error((err == NGX_EINTR) ? NGX_LOG_INFO : NGX_LOG_ALERT,
                      cycle->log, err, "sigtimedwait() failed");
        return NGX_ERROR;
    }

    ngx_log_debug3(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "rtsig signo:%d fd:%d band:%04Xd",
                   signo, si.si_fd, si.si_band);

    if (flags & NGX_UPDATE_TIME) {
        ngx_time_update();
    }

    rtscf = ngx_event_get_conf(ngx_cycle->conf_ctx, ngx_rtsig_module);

    if (signo == (int) rtscf->signo || signo == (int) rtscf->signo + 1) {

        if (overflow && (ngx_uint_t) si.si_fd > overflow_current) {
            return NGX_OK;
        }

        c = ngx_cycle->files[si.si_fd];

        if (c == NULL) {

            /* the stale event */

            return NGX_OK;
        }

        instance = signo - (int) rtscf->signo;

        rev = c->read;

        if (rev->instance != instance) {

            /*
             * the stale event from a file descriptor
             * that was just closed in this iteration
             */

            ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                           "rtsig: stale event %p", c);

            return NGX_OK;
        }

        if ((si.si_band & (POLLIN|POLLHUP|POLLERR)) && rev->active) {

            rev->ready = 1;

            if (flags & NGX_POST_EVENTS) {
                queue = rev->accept ? &ngx_posted_accept_events
                                    : &ngx_posted_events;

                ngx_post_event(rev, queue);

            } else {
                rev->handler(rev);
            }
        }

        wev = c->write;

        if ((si.si_band & (POLLOUT|POLLHUP|POLLERR)) && wev->active) {

            wev->ready = 1;

            if (flags & NGX_POST_EVENTS) {
                ngx_post_event(wev, &ngx_posted_events);

            } else {
                wev->handler(wev);
            }
        }

        return NGX_OK;

    } else if (signo == SIGALRM) {

        ngx_time_update();

        return NGX_OK;

    } else if (signo == SIGIO) {

        ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                      "rt signal queue overflowed");

        /* flush the RT signal queue */

        ngx_memzero(&sa, sizeof(struct sigaction));
        sa.sa_handler = SIG_DFL;
        sigemptyset(&sa.sa_mask);

        if (sigaction(rtscf->signo, &sa, NULL) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "sigaction(%d, SIG_DFL) failed", rtscf->signo);
        }

        if (sigaction(rtscf->signo + 1, &sa, NULL) == -1) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "sigaction(%d, SIG_DFL) failed", rtscf->signo + 1);
        }

        overflow = 1;
        overflow_current = 0;
        ngx_event_actions.process_events = ngx_rtsig_process_overflow;

        return NGX_ERROR;

    }

    ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                  "sigtimedwait() returned unexpected signal: %d", signo);

    return NGX_ERROR;
}