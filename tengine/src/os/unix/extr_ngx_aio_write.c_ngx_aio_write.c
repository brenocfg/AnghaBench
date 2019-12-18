#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct aiocb {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_10__ {TYPE_3__* sigval_ptr; } ;
struct TYPE_11__ {TYPE_1__ sigev_value; int /*<<< orphan*/  sigev_notify; int /*<<< orphan*/  sigev_notify_kqueue; } ;
struct TYPE_14__ {size_t aio_nbytes; TYPE_2__ aio_sigevent; int /*<<< orphan*/ * aio_buf; int /*<<< orphan*/  aio_fildes; } ;
struct TYPE_12__ {int ready; int complete; int active; int error; int /*<<< orphan*/  log; TYPE_5__ aiocb; } ;
typedef  TYPE_3__ ngx_event_t ;
struct TYPE_13__ {int /*<<< orphan*/  fd; TYPE_3__* write; } ;
typedef  TYPE_4__ ngx_connection_t ;

/* Variables and functions */
 int NGX_AGAIN ; 
 int NGX_EINPROGRESS ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  SIGEV_KEVENT ; 
 int aio_error (TYPE_5__*) ; 
 int aio_return (TYPE_5__*) ; 
 int aio_write (TYPE_5__*) ; 
 int ngx_errno ; 
 int /*<<< orphan*/  ngx_kqueue ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,...) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 

ssize_t
ngx_aio_write(ngx_connection_t *c, u_char *buf, size_t size)
{
    int           n;
    ngx_event_t  *wev;

    wev = c->write;

    if (!wev->ready) {
        return NGX_AGAIN;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, wev->log, 0,
                   "aio: wev->complete: %d", wev->complete);

    if (!wev->complete) {
        ngx_memzero(&wev->aiocb, sizeof(struct aiocb));

        wev->aiocb.aio_fildes = c->fd;
        wev->aiocb.aio_buf = buf;
        wev->aiocb.aio_nbytes = size;

#if (NGX_HAVE_KQUEUE)
        wev->aiocb.aio_sigevent.sigev_notify_kqueue = ngx_kqueue;
        wev->aiocb.aio_sigevent.sigev_notify = SIGEV_KEVENT;
        wev->aiocb.aio_sigevent.sigev_value.sigval_ptr = wev;
#endif

        if (aio_write(&wev->aiocb) == -1) {
            ngx_log_error(NGX_LOG_CRIT, wev->log, ngx_errno,
                          "aio_write() failed");
            return NGX_ERROR;
        }

        ngx_log_debug0(NGX_LOG_DEBUG_EVENT, wev->log, 0, "aio_write: OK");

        wev->active = 1;
        wev->ready = 0;
    }

    wev->complete = 0;

    n = aio_error(&wev->aiocb);
    if (n == -1) {
        ngx_log_error(NGX_LOG_CRIT, wev->log, ngx_errno, "aio_error() failed");
        wev->error = 1;
        return NGX_ERROR;
    }

    if (n != 0) {
        if (n == NGX_EINPROGRESS) {
            if (wev->ready) {
                ngx_log_error(NGX_LOG_ALERT, wev->log, n,
                              "aio_write() still in progress");
                wev->ready = 0;
            }
            return NGX_AGAIN;
        }

        ngx_log_error(NGX_LOG_CRIT, wev->log, n, "aio_write() failed");
        wev->error = 1;
        wev->ready = 0;

#if 1
        n = aio_return(&wev->aiocb);
        if (n == -1) {
            ngx_log_error(NGX_LOG_ALERT, wev->log, ngx_errno,
                          "aio_return() failed");
        }

        ngx_log_error(NGX_LOG_CRIT, wev->log, n, "aio_return() %d", n);
#endif

        return NGX_ERROR;
    }

    n = aio_return(&wev->aiocb);
    if (n == -1) {
        ngx_log_error(NGX_LOG_ALERT, wev->log, ngx_errno,
                      "aio_return() failed");

        wev->error = 1;
        wev->ready = 0;
        return NGX_ERROR;
    }


    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, wev->log, 0, "aio_write: %d", n);

    wev->active = 0;
    wev->ready = 1;

    return n;
}