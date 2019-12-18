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
typedef  int ssize_t ;
typedef  scalar_t__ off_t ;
struct TYPE_7__ {size_t size; int /*<<< orphan*/  count; int /*<<< orphan*/  iovs; } ;
typedef  TYPE_2__ ngx_iovec_t ;
struct TYPE_6__ {int /*<<< orphan*/  data; } ;
struct TYPE_8__ {scalar_t__ sys_offset; int offset; TYPE_1__ name; int /*<<< orphan*/  log; int /*<<< orphan*/  fd; } ;
typedef  TYPE_3__ ngx_file_t ;
typedef  scalar_t__ ngx_err_t ;

/* Variables and functions */
 scalar_t__ NGX_EINTR ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_CORE ; 
 int /*<<< orphan*/  SEEK_SET ; 
 int lseek (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_errno ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*) ; 
 int /*<<< orphan*/  ngx_log_debug3 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,size_t,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int /*<<< orphan*/ ,...) ; 
 int pwritev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__) ; 
 int writev (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ssize_t
ngx_writev_file(ngx_file_t *file, ngx_iovec_t *vec, off_t offset)
{
    ssize_t    n;
    ngx_err_t  err;

    ngx_log_debug3(NGX_LOG_DEBUG_CORE, file->log, 0,
                   "writev: %d, %uz, %O", file->fd, vec->size, offset);

#if (NGX_HAVE_PWRITEV)

eintr:

    n = pwritev(file->fd, vec->iovs, vec->count, offset);

    if (n == -1) {
        err = ngx_errno;

        if (err == NGX_EINTR) {
            ngx_log_debug0(NGX_LOG_DEBUG_CORE, file->log, err,
                           "pwritev() was interrupted");
            goto eintr;
        }

        ngx_log_error(NGX_LOG_CRIT, file->log, err,
                      "pwritev() \"%s\" failed", file->name.data);
        return NGX_ERROR;
    }

    if ((size_t) n != vec->size) {
        ngx_log_error(NGX_LOG_CRIT, file->log, 0,
                      "pwritev() \"%s\" has written only %z of %uz",
                      file->name.data, n, vec->size);
        return NGX_ERROR;
    }

#else

    if (file->sys_offset != offset) {
        if (lseek(file->fd, offset, SEEK_SET) == -1) {
            ngx_log_error(NGX_LOG_CRIT, file->log, ngx_errno,
                          "lseek() \"%s\" failed", file->name.data);
            return NGX_ERROR;
        }

        file->sys_offset = offset;
    }

eintr:

    n = writev(file->fd, vec->iovs, vec->count);

    if (n == -1) {
        err = ngx_errno;

        if (err == NGX_EINTR) {
            ngx_log_debug0(NGX_LOG_DEBUG_CORE, file->log, err,
                           "writev() was interrupted");
            goto eintr;
        }

        ngx_log_error(NGX_LOG_CRIT, file->log, err,
                      "writev() \"%s\" failed", file->name.data);
        return NGX_ERROR;
    }

    if ((size_t) n != vec->size) {
        ngx_log_error(NGX_LOG_CRIT, file->log, 0,
                      "writev() \"%s\" has written only %z of %uz",
                      file->name.data, n, vec->size);
        return NGX_ERROR;
    }

    file->sys_offset += n;

#endif

    file->offset += n;

    return n;
}