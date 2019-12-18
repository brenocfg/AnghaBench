#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ssize_t ;
typedef  scalar_t__ ngx_int_t ;
struct TYPE_6__ {int /*<<< orphan*/  ft_type; TYPE_1__* request; int /*<<< orphan*/  buf_in; int /*<<< orphan*/  buffer; } ;
typedef  TYPE_3__ ngx_http_lua_socket_tcp_upstream_t ;
struct TYPE_5__ {int /*<<< orphan*/  log; } ;
struct TYPE_4__ {TYPE_2__* connection; } ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 int /*<<< orphan*/  NGX_HTTP_LUA_SOCKET_FT_CLOSED ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 scalar_t__ ngx_http_lua_read_line (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_socket_read_line(void *data, ssize_t bytes)
{
    ngx_http_lua_socket_tcp_upstream_t      *u = data;

    ngx_int_t                    rc;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, u->request->connection->log, 0,
                   "lua tcp socket read line");

    rc = ngx_http_lua_read_line(&u->buffer, u->buf_in, bytes,
                                u->request->connection->log);
    if (rc == NGX_ERROR) {
        u->ft_type |= NGX_HTTP_LUA_SOCKET_FT_CLOSED;
        return NGX_ERROR;
    }

    return rc;
}