#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_OK ; 

__attribute__((used)) static ngx_int_t
ngx_iocp_del_connection(ngx_connection_t *c, ngx_uint_t flags)
{
#if 0
    if (flags & NGX_CLOSE_EVENT) {
        return NGX_OK;
    }

    if (CancelIo((HANDLE) c->fd) == 0) {
        ngx_log_error(NGX_LOG_ALERT, c->log, ngx_errno, "CancelIo() failed");
        return NGX_ERROR;
    }
#endif

    return NGX_OK;
}