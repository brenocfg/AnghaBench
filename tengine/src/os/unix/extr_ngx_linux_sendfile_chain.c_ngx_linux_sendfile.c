#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int ssize_t ;
typedef  int /*<<< orphan*/  off_t ;
typedef  int ngx_err_t ;
struct TYPE_14__ {int /*<<< orphan*/  log; TYPE_1__* write; int /*<<< orphan*/  fd; } ;
typedef  TYPE_4__ ngx_connection_t ;
struct TYPE_15__ {scalar_t__ file_pos; TYPE_3__* file; } ;
typedef  TYPE_5__ ngx_buf_t ;
typedef  scalar_t__ int32_t ;
struct TYPE_12__ {int /*<<< orphan*/  data; } ;
struct TYPE_13__ {TYPE_2__ name; int /*<<< orphan*/  fd; scalar_t__ thread_handler; } ;
struct TYPE_11__ {int error; } ;

/* Variables and functions */
 int NGX_AGAIN ; 
#define  NGX_EAGAIN 129 
#define  NGX_EINTR 128 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_ALERT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_EVENT ; 
 int /*<<< orphan*/  ngx_connection_error (TYPE_4__*,int,char*) ; 
 int ngx_errno ; 
 int ngx_linux_sendfile_thread (TYPE_4__*,TYPE_5__*,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,scalar_t__,size_t) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,scalar_t__) ; 
 int sendfile (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__*,size_t) ; 

__attribute__((used)) static ssize_t
ngx_linux_sendfile(ngx_connection_t *c, ngx_buf_t *file, size_t size)
{
#if (NGX_HAVE_SENDFILE64)
    off_t      offset;
#else
    int32_t    offset;
#endif
    ssize_t    n;
    ngx_err_t  err;

#if (NGX_THREADS)

    if (file->file->thread_handler) {
        return ngx_linux_sendfile_thread(c, file, size);
    }

#endif

#if (NGX_HAVE_SENDFILE64)
    offset = file->file_pos;
#else
    offset = (int32_t) file->file_pos;
#endif

eintr:

    ngx_log_debug2(NGX_LOG_DEBUG_EVENT, c->log, 0,
                   "sendfile: @%O %uz", file->file_pos, size);

    n = sendfile(c->fd, file->file->fd, &offset, size);

    if (n == -1) {
        err = ngx_errno;

        switch (err) {
        case NGX_EAGAIN:
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                           "sendfile() is not ready");
            return NGX_AGAIN;

        case NGX_EINTR:
            ngx_log_debug0(NGX_LOG_DEBUG_EVENT, c->log, err,
                           "sendfile() was interrupted");
            goto eintr;

        default:
            c->write->error = 1;
            ngx_connection_error(c, err, "sendfile() failed");
            return NGX_ERROR;
        }
    }

    if (n == 0) {
        /*
         * if sendfile returns zero, then someone has truncated the file,
         * so the offset became beyond the end of the file
         */

        ngx_log_error(NGX_LOG_ALERT, c->log, 0,
                      "sendfile() reported that \"%s\" was truncated at %O",
                      file->file->name.data, file->file_pos);

        return NGX_ERROR;
    }

    ngx_log_debug3(NGX_LOG_DEBUG_EVENT, c->log, 0, "sendfile: %z of %uz @%O",
                   n, size, file->file_pos);

    return n;
}