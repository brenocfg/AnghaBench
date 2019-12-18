#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
struct TYPE_7__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  log; int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ ngx_file_t ;
struct TYPE_8__ {int ready; scalar_t__ active; } ;
typedef  TYPE_2__ ngx_event_t ;
struct TYPE_9__ {int err; int nbytes; int /*<<< orphan*/  aiocb; } ;
typedef  TYPE_3__ ngx_event_aio_t ;
typedef  int ngx_err_t ;

/* Variables and functions */
 int NGX_AGAIN ; 
 int NGX_EINPROGRESS ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int aio_error (int /*<<< orphan*/ *) ; 
 int aio_return (int /*<<< orphan*/ *) ; 
 int ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static ssize_t
ngx_file_aio_result(ngx_file_t *file, ngx_event_aio_t *aio, ngx_event_t *ev)
{
    int        n;
    ngx_err_t  err;

    n = aio_error(&aio->aiocb);

    ngx_log_debug2(NGX_LOG_DEBUG_CORE, file->log, 0,
                   "aio_error: fd:%d %d", file->fd, n);

    if (n == -1) {
        err = ngx_errno;
        aio->err = err;

        ngx_log_error(NGX_LOG_ALERT, file->log, err,
                      "aio_error(\"%V\") failed", &file->name);
        return NGX_ERROR;
    }

    if (n == NGX_EINPROGRESS) {
        if (ev->ready) {
            ev->ready = 0;
            ngx_log_error(NGX_LOG_ALERT, file->log, n,
                          "aio_read(\"%V\") still in progress",
                          &file->name);
        }

        return NGX_AGAIN;
    }

    n = aio_return(&aio->aiocb);

    if (n == -1) {
        err = ngx_errno;
        aio->err = err;
        ev->ready = 1;

        ngx_log_error(NGX_LOG_CRIT, file->log, err,
                      "aio_return(\"%V\") failed", &file->name);
        return NGX_ERROR;
    }

    aio->err = 0;
    aio->nbytes = n;
    ev->ready = 1;
    ev->active = 0;

    ngx_log_debug2(NGX_LOG_DEBUG_CORE, file->log, 0,
                   "aio_return: fd:%d %d", file->fd, n);

    return n;
}