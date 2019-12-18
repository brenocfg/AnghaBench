#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_21__   TYPE_7__ ;
typedef  struct TYPE_20__   TYPE_4__ ;
typedef  struct TYPE_19__   TYPE_3__ ;
typedef  struct TYPE_18__   TYPE_2__ ;
typedef  struct TYPE_17__   TYPE_1__ ;
typedef  struct TYPE_16__   TYPE_14__ ;
typedef  struct TYPE_15__   TYPE_13__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  rtsig_nr ;
typedef  int /*<<< orphan*/  rtsig_max ;
typedef  size_t ngx_uint_t ;
struct TYPE_17__ {size_t overflow_events; size_t overflow_test; scalar_t__ overflow_threshold; } ;
typedef  TYPE_1__ ngx_rtsig_conf_t ;
typedef  int /*<<< orphan*/  ngx_queue_t ;
typedef  int /*<<< orphan*/  ngx_msec_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_18__ {int ready; int /*<<< orphan*/  (* handler ) (TYPE_2__*) ;int /*<<< orphan*/  closed; scalar_t__ active; scalar_t__ accept; } ;
typedef  TYPE_2__ ngx_event_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_19__ {scalar_t__ connection_n; int /*<<< orphan*/  log; TYPE_4__** files; } ;
typedef  TYPE_3__ ngx_cycle_t ;
struct TYPE_20__ {int fd; TYPE_2__* write; TYPE_2__* read; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_21__ {int fd; int events; int revents; } ;
struct TYPE_16__ {int /*<<< orphan*/  conf_ctx; } ;
struct TYPE_15__ {scalar_t__ (* process_events ) (TYPE_3__*,int /*<<< orphan*/ ,size_t) ;} ;

/* Variables and functions */
 int CTL_KERN ; 
 int KERN_RTSIGMAX ; 
 int KERN_RTSIGNR ; 
 scalar_t__ NGX_EINTR ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  NGX_LOG_INFO ; 
 scalar_t__ NGX_OK ; 
 size_t NGX_POST_EVENTS ; 
 size_t NGX_UPDATE_TIME ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 int /*<<< orphan*/  errno ; 
 TYPE_14__* ngx_cycle ; 
 scalar_t__ ngx_errno ; 
 TYPE_13__ ngx_event_actions ; 
 TYPE_1__* ngx_event_get_conf (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_linux_rtsig_max ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_2__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_accept_events ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_rtsig_module ; 
 scalar_t__ ngx_rtsig_process_events (TYPE_3__*,int /*<<< orphan*/ ,size_t) ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 scalar_t__ overflow ; 
 scalar_t__ overflow_current ; 
 TYPE_7__* overflow_list ; 
 int poll (TYPE_7__*,size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (TYPE_2__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_2__*) ; 
 int sysctl (int*,int,int*,size_t*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_rtsig_process_overflow(ngx_cycle_t *cycle, ngx_msec_t timer,
    ngx_uint_t flags)
{
    int                name[2], rtsig_max, rtsig_nr, events, ready;
    size_t             len;
    ngx_err_t          err;
    ngx_uint_t         tested, n, i;
    ngx_event_t       *rev, *wev;
    ngx_queue_t       *queue;
    ngx_connection_t  *c;
    ngx_rtsig_conf_t  *rtscf;

    ngx_log_debug0(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "rtsig process overflow");

    rtscf = ngx_event_get_conf(ngx_cycle->conf_ctx, ngx_rtsig_module);

    tested = 0;

    for ( ;; ) {

        n = 0;
        while (n < rtscf->overflow_events) {

            if (overflow_current == cycle->connection_n) {
                break;
            }

            c = cycle->files[overflow_current++];

            if (c == NULL || c->fd == -1) {
                continue;
            }

            events = 0;

            if (c->read->active && c->read->handler) {
                events |= POLLIN;
            }

            if (c->write->active && c->write->handler) {
                events |= POLLOUT;
            }

            if (events == 0) {
                continue;
            }

            overflow_list[n].fd = c->fd;
            overflow_list[n].events = events;
            overflow_list[n].revents = 0;
            n++;
        }

        if (n == 0) {
            break;
        }

        for ( ;; ) {
            ready = poll(overflow_list, n, 0);

            ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                           "rtsig overflow poll:%d", ready);

            if (ready == -1) {
                err = ngx_errno;
                ngx_log_error((err == NGX_EINTR) ? NGX_LOG_INFO : NGX_LOG_ALERT,
                              cycle->log, 0,
                              "poll() failed while the overflow recover");

                if (err == NGX_EINTR) {
                    continue;
                }
            }

            break;
        }

        if (ready <= 0) {
            continue;
        }

        for (i = 0; i < n; i++) {
            c = cycle->files[overflow_list[i].fd];

            if (c == NULL) {
                continue;
            }

            rev = c->read;

            if (rev->active
                && !rev->closed
                && rev->handler
                && (overflow_list[i].revents
                                          & (POLLIN|POLLERR|POLLHUP|POLLNVAL)))
            {
                tested++;

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

            if (wev->active
                && !wev->closed
                && wev->handler
                && (overflow_list[i].revents
                                         & (POLLOUT|POLLERR|POLLHUP|POLLNVAL)))
            {
                tested++;

                wev->ready = 1;

                if (flags & NGX_POST_EVENTS) {
                    ngx_post_event(wev, &ngx_posted_events);

                } else {
                    wev->handler(wev);
                }
            }
        }

        if (tested >= rtscf->overflow_test) {

            if (ngx_linux_rtsig_max) {

                /*
                 * Check the current rt queue length to prevent
                 * the new overflow.
                 *
                 * learn the "/proc/sys/kernel/rtsig-max" value because
                 * it can be changed since the last checking
                 */

                name[0] = CTL_KERN;
                name[1] = KERN_RTSIGMAX;
                len = sizeof(rtsig_max);

                if (sysctl(name, 2, &rtsig_max, &len, NULL, 0) == -1) {
                    ngx_log_error(NGX_LOG_ALERT, cycle->log, errno,
                                  "sysctl(KERN_RTSIGMAX) failed");
                    return NGX_ERROR;
                }

                /* name[0] = CTL_KERN; */
                name[1] = KERN_RTSIGNR;
                len = sizeof(rtsig_nr);

                if (sysctl(name, 2, &rtsig_nr, &len, NULL, 0) == -1) {
                    ngx_log_error(NGX_LOG_ALERT, cycle->log, errno,
                                  "sysctl(KERN_RTSIGNR) failed");
                    return NGX_ERROR;
                }

                /*
                 * drain the rt signal queue if the /"proc/sys/kernel/rtsig-nr"
                 * is bigger than
                 *    "/proc/sys/kernel/rtsig-max" / "rtsig_overflow_threshold"
                 */

                if (rtsig_max / (int) rtscf->overflow_threshold < rtsig_nr) {
                    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                                   "rtsig queue state: %d/%d",
                                   rtsig_nr, rtsig_max);
                    while (ngx_rtsig_process_events(cycle, 0, flags) == NGX_OK)
                    {
                        /* void */
                    }
                }

            } else {

                /*
                 * Linux has not KERN_RTSIGMAX since 2.6.6-mm2
                 * so drain the rt signal queue unconditionally
                 */

                while (ngx_rtsig_process_events(cycle, 0, flags) == NGX_OK) {
                    /* void */
                }
            }

            tested = 0;
        }
    }

    if (flags & NGX_UPDATE_TIME) {
        ngx_time_update();
    }

    ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                  "rt signal queue overflow recovered");

    overflow = 0;
    ngx_event_actions.process_events = ngx_rtsig_process_events;

    return NGX_OK;
}