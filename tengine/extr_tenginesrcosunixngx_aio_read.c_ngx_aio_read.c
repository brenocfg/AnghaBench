#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct aiocb {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_10__ {size_t aio_fildes; size_t aio_nbytes; int /*<<< orphan*/ * aio_buf; } ;
struct TYPE_8__ {int ready; size_t complete; int error; int active; int eof; int /*<<< orphan*/  log; TYPE_3__ aiocb; } ;
typedef  TYPE_1__ ngx_event_t ;
struct TYPE_9__ {size_t fd; int /*<<< orphan*/  log; TYPE_1__* read; } ;
typedef  TYPE_2__ ngx_connection_t ;

/* Variables and functions */
 int NGX_AGAIN ; 
 int NGX_EINPROGRESS ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int aio_error (TYPE_3__*) ; 
 int aio_read (TYPE_3__*) ; 
 int aio_return (TYPE_3__*) ; 
 int ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,size_t,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_3__*,int) ; 

ssize_t
ngx_aio_read(ngx_connection_t *c, u_char *buf, size_t size)
{
    int           n;
    ngx_event_t  *rev;

    rev = c->read;

    if (!rev->ready) {
        ngx_log_error(NGX_LOG_ALERT, c->log, 0, "second aio post");
        return NGX_AGAIN;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "rev->complete: %d", rev->complete);
    ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "aio size: %d", size);

    if (!rev->complete) {
        ngx_memzero(&rev->aiocb, sizeof(struct aiocb));

        rev->aiocb.aio_fildes = c->fd;
        rev->aiocb.aio_buf = buf;
        rev->aiocb.aio_nbytes = size;

#if (NGX_HAVE_KQUEUE)
        rev->aiocb.aio_sigevent.sigev_notify_kqueue = ngx_kqueue;
        rev->aiocb.aio_sigevent.sigev_notify = SIGEV_KEVENT;
        rev->aiocb.aio_sigevent.sigev_value.sigval_ptr = rev;
#endif

        if (aio_read(&rev->aiocb) == -1) {
            ngx_log_error(NGX_LOG_CRIT, rev->log, ngx_errno,
                          "aio_read() failed");
            rev->error = 1;
            return NGX_ERROR;
        }

        ngx_log_debug1(NGX_LOG_DEBUG_EVENT, c->log, 0,
                       "aio_read: #%d OK", c->fd);

        rev->active = 1;
        rev->ready = 0;
    }

    rev->complete = 0;

    n = aio_error(&rev->aiocb);
    if (n == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno, "aio_error() failed");
        rev->error = 1;
        return NGX_ERROR;
    }

    if (n != 0) {
        if (n == NGX_EINPROGRESS) {
            if (rev->ready) {
                ngx_log_error(NGX_LOG_ALERT, c->log, n,
                              "aio_read() still in progress");
                rev->ready = 0;
            }
            return NGX_AGAIN;
        }

        ngx_log_error(NGX_LOG_CRIT, c->log, n, "aio_read() failed");
        rev->error = 1;
        rev->ready = 0;
        return NGX_ERROR;
    }

    n = aio_return(&rev->aiocb);
    if (n == -1) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno,
                      "aio_return() failed");

        rev->error = 1;
        rev->ready = 0;
        return NGX_ERROR;
    }

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, rev->log, 0,
                   "aio_read: #%d %d", c->fd, n);

    if (n == 0) {
        rev->eof = 1;
        rev->ready = 0;
    } else {
        rev->ready = 1;
    }

    rev->active = 0;

    return n;
}