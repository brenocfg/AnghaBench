#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int ngx_int_t ;
typedef  scalar_t__ ngx_err_t ;
struct TYPE_3__ {int /*<<< orphan*/  fd; int /*<<< orphan*/  log; } ;
typedef  TYPE_1__ ngx_connection_t ;

/* Variables and functions */
 int /*<<< orphan*/  MSG_PEEK ; 
 scalar_t__ NGX_EAGAIN ; 
 int NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int NGX_OK ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,scalar_t__,char*,int,int /*<<< orphan*/ ) ; 
 scalar_t__ ngx_socket_errno ; 
 int recv (int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ngx_int_t
ngx_http_upstream_check_peek_one_byte(ngx_connection_t *c)
{
    char                            buf[1];
    ngx_int_t                       n;
    ngx_err_t                       err;

    n = recv(c->fd, buf, 1, MSG_PEEK);
    err = ngx_socket_errno;

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, c->log, err,
                   "http check upstream recv(): %i, fd: %d",
                   n, c->fd);

    if (n == 1 || (n == -1 && err == NGX_EAGAIN)) {
        return NGX_OK;
    } else {
        return NGX_ERROR;
    }
}