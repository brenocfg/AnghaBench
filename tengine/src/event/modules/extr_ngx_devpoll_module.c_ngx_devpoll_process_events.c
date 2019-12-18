#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_9__ ;
typedef  struct TYPE_13__   TYPE_8__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
struct pollfd {int dp_nfds; size_t fd; scalar_t__ revents; scalar_t__ events; scalar_t__ dp_timeout; TYPE_9__* dp_fds; } ;
struct dvpoll {int dp_nfds; size_t fd; scalar_t__ revents; scalar_t__ events; scalar_t__ dp_timeout; TYPE_9__* dp_fds; } ;
typedef  scalar_t__ ssize_t ;
typedef  int ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_queue_t ;
typedef  scalar_t__ ngx_msec_t ;
typedef  int ngx_int_t ;
typedef  size_t ngx_fd_t ;
struct TYPE_10__ {int ready; int instance; int /*<<< orphan*/  (* handler ) (TYPE_1__*) ;scalar_t__ active; scalar_t__ accept; } ;
typedef  TYPE_1__ ngx_event_t ;
typedef  int ngx_err_t ;
struct TYPE_11__ {int /*<<< orphan*/  log; } ;
typedef  TYPE_2__ ngx_cycle_t ;
struct TYPE_12__ {int fd; TYPE_1__* write; TYPE_1__* read; } ;
typedef  TYPE_3__ ngx_connection_t ;
struct TYPE_14__ {size_t fd; int revents; int /*<<< orphan*/  events; } ;
struct TYPE_13__ {TYPE_3__** files; } ;

/* Variables and functions */
 int /*<<< orphan*/  DP_ISPOLLED ; 
 int /*<<< orphan*/  DP_POLL ; 
 int NGX_EINTR ; 
 int NGX_ERROR ; 
 int NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int NGX_LOG_INFO ; 
 int NGX_OK ; 
 int NGX_POST_EVENTS ; 
 scalar_t__ NGX_TIMER_INFINITE ; 
 int NGX_UPDATE_TIME ; 
 int POLLERR ; 
 int POLLHUP ; 
 int POLLIN ; 
 int POLLNVAL ; 
 int POLLOUT ; 
 scalar_t__ POLLREMOVE ; 
 struct pollfd* change_list ; 
 int close (size_t) ; 
 int /*<<< orphan*/  dp ; 
 TYPE_9__* event_list ; 
 int ioctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct pollfd*) ; 
 int nchanges ; 
 scalar_t__ nevents ; 
 TYPE_8__* ngx_cycle ; 
 int ngx_errno ; 
 scalar_t__ ngx_event_timer_alarm ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_error (int,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  ngx_post_event (TYPE_1__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_posted_accept_events ; 
 int /*<<< orphan*/  ngx_posted_events ; 
 int /*<<< orphan*/  ngx_time_update () ; 
 int /*<<< orphan*/  stub1 (TYPE_1__*) ; 
 int /*<<< orphan*/  stub2 (TYPE_1__*) ; 
 scalar_t__ write (int /*<<< orphan*/ ,struct pollfd*,int) ; 

__attribute__((used)) static ngx_int_t
ngx_devpoll_process_events(ngx_cycle_t *cycle, ngx_msec_t timer,
    ngx_uint_t flags)
{
    int                 events, revents, rc;
    size_t              n;
    ngx_fd_t            fd;
    ngx_err_t           err;
    ngx_int_t           i;
    ngx_uint_t          level, instance;
    ngx_event_t        *rev, *wev;
    ngx_queue_t        *queue;
    ngx_connection_t   *c;
    struct pollfd       pfd;
    struct dvpoll       dvp;

    /* NGX_TIMER_INFINITE == INFTIM */

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                   "devpoll timer: %M", timer);

    if (nchanges) {
        n = nchanges * sizeof(struct pollfd);
        if (write(dp, change_list, n) != (ssize_t) n) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                          "write(/dev/poll) failed");
            return NGX_ERROR;
        }

        nchanges = 0;
    }

    dvp.dp_fds = event_list;
    dvp.dp_nfds = (int) nevents;
    dvp.dp_timeout = timer;
    events = ioctl(dp, DP_POLL, &dvp);

    err = (events == -1) ? ngx_errno : 0;

    if (flags & NGX_UPDATE_TIME || ngx_event_timer_alarm) {
        ngx_time_update();
    }

    if (err) {
        if (err == NGX_EINTR) {

            if (ngx_event_timer_alarm) {
                ngx_event_timer_alarm = 0;
                return NGX_OK;
            }

            level = NGX_LOG_INFO;

        } else {
            level = NGX_LOG_ALERT;
        }

        ngx_log_error(level, cycle->log, err, "ioctl(DP_POLL) failed");
        return NGX_ERROR;
    }

    if (events == 0) {
        if (timer != NGX_TIMER_INFINITE) {
            return NGX_OK;
        }

        ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                      "ioctl(DP_POLL) returned no events without timeout");
        return NGX_ERROR;
    }

    for (i = 0; i < events; i++) {

        fd = event_list[i].fd;
        revents = event_list[i].revents;

        c = ngx_cycle->files[fd];

        if (c == NULL || c->fd == -1) {

            pfd.fd = fd;
            pfd.events = 0;
            pfd.revents = 0;

            rc = ioctl(dp, DP_ISPOLLED, &pfd);

            switch (rc) {

            case -1:
                ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                    "ioctl(DP_ISPOLLED) failed for socket %d, event %04Xd",
                    fd, revents);
                break;

            case 0:
                ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                    "phantom event %04Xd for closed and removed socket %d",
                    revents, fd);
                break;

            default:
                ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                    "unexpected event %04Xd for closed and removed socket %d, "
                    "ioctl(DP_ISPOLLED) returned rc:%d, fd:%d, event %04Xd",
                    revents, fd, rc, pfd.fd, pfd.revents);

                pfd.fd = fd;
                pfd.events = POLLREMOVE;
                pfd.revents = 0;

                if (write(dp, &pfd, sizeof(struct pollfd))
                    != (ssize_t) sizeof(struct pollfd))
                {
                    ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                                  "write(/dev/poll) for %d failed", fd);
                }

                if (close(fd) == -1) {
                    ngx_log_error(NGX_LOG_ALERT, cycle->log, ngx_errno,
                                  "close(%d) failed", fd);
                }

                break;
            }

            continue;
        }

        ngx_log_debug3(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                       "devpoll: fd:%d, ev:%04Xd, rev:%04Xd",
                       fd, event_list[i].events, revents);

        if (revents & (POLLERR|POLLHUP|POLLNVAL)) {
            ngx_log_debug3(NGX_LOG_DEBUG_EVENT, cycle->log, 0,
                          "ioctl(DP_POLL) error fd:%d ev:%04Xd rev:%04Xd",
                          fd, event_list[i].events, revents);
        }

        if (revents & ~(POLLIN|POLLOUT|POLLERR|POLLHUP|POLLNVAL)) {
            ngx_log_error(NGX_LOG_ALERT, cycle->log, 0,
                          "strange ioctl(DP_POLL) events "
                          "fd:%d ev:%04Xd rev:%04Xd",
                          fd, event_list[i].events, revents);
        }

        if (revents & (POLLERR|POLLHUP|POLLNVAL)) {

            /*
             * if the error events were returned, add POLLIN and POLLOUT
             * to handle the events at least in one active handler
             */

            revents |= POLLIN|POLLOUT;
        }

        rev = c->read;

        if ((revents & POLLIN) && rev->active) {
            rev->ready = 1;

            if (flags & NGX_POST_EVENTS) {
                queue = rev->accept ? &ngx_posted_accept_events
                                    : &ngx_posted_events;

                ngx_post_event(rev, queue);

            } else {
                instance = rev->instance;

                rev->handler(rev);

                if (c->fd == -1 || rev->instance != instance) {
                    continue;
                }
            }
        }

        wev = c->write;

        if ((revents & POLLOUT) && wev->active) {
            wev->ready = 1;

            if (flags & NGX_POST_EVENTS) {
                ngx_post_event(wev, &ngx_posted_events);

            } else {
                wev->handler(wev);
            }
        }
    }

    return NGX_OK;
}