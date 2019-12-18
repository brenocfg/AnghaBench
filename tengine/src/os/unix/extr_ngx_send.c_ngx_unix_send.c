#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ssize_t ;
struct TYPE_5__ {scalar_t__ kq_errno; int error; scalar_t__ ready; scalar_t__ pending_eof; } ;
typedef  TYPE_1__ ngx_event_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_6__ {int /*<<< orphan*/  log; int /*<<< orphan*/  sent; int /*<<< orphan*/  fd; TYPE_1__* write; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 scalar_t__ NGX_AGAIN ; 
 scalar_t__ NGX_EAGAIN ; 
 scalar_t__ NGX_EINTR ; 
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int NGX_USE_KQUEUE_EVENT ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_2__*,scalar_t__,char*) ; 
 int ngx_event_flags ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__,size_t) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 scalar_t__ ngx_socket_errno ; 
 scalar_t__ send (int /*<<< orphan*/ ,int /*<<< orphan*/ *,size_t,int /*<<< orphan*/ ) ; 

ssize_t
ngx_unix_send(ngx_connection_t *c, u_char *buf, size_t size)
{
    ssize_t       n;
    ngx_err_t     err;
    ngx_event_t  *wev;

    wev = c->write;

#if (NGX_HAVE_KQUEUE)

    if ((ngx_event_flags & NGX_USE_KQUEUE_EVENT) && wev->pending_eof) {
        (void) ngx_connection_error(c, wev->kq_errno,
                               "kevent() reported about an closed connection");
        wev->error = 1;
        return NGX_ERROR;
    }

#endif

    for ( ;; ) {
        n = send(c->fd, buf, size, 0);

        ngx_log_debug3(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "send: fd:%d %z of %uz", c->fd, n, size);

        if (n > 0) {
            if (n < (ssize_t) size) {
                wev->ready = 0;
            }

            c->sent += n;

            return n;
        }

        err = ngx_socket_errno;

        if (n == 0) {
            ngx_log_error(NGX_LOG_ALERT, c->log, err, "send() returned zero");
            wev->ready = 0;
            return n;
        }

        if (err == NGX_EAGAIN || err == NGX_EINTR) {
            wev->ready = 0;

            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                           "send() not ready");

            if (err == NGX_EAGAIN) {
                return NGX_AGAIN;
            }

        } else {
            wev->error = 1;
            (void) ngx_connection_error(c, err, "send() failed");
            return NGX_ERROR;
        }
    }
}