#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
struct TYPE_7__ {scalar_t__ no_close; scalar_t__ ft_type; TYPE_1__* read_co_ctx; } ;
typedef  TYPE_2__ ngx_http_lua_socket_tcp_upstream_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_6__ {int /*<<< orphan*/ * cleanup; } ;

/* Variables and functions */
 int ngx_http_lua_socket_prepare_error_retvals (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_finalize_read_part (int /*<<< orphan*/ *,TYPE_2__*) ; 

__attribute__((used)) static int
ngx_http_lua_socket_read_error_retval_handler(ngx_http_request_t *r,
    ngx_http_lua_socket_tcp_upstream_t *u, lua_State *L)
{
    ngx_uint_t          ft_type;

    if (u->read_co_ctx) {
        u->read_co_ctx->cleanup = NULL;
    }

    ft_type = u->ft_type;
    u->ft_type = 0;

    if (u->no_close) {
        u->no_close = 0;

    } else {
        ngx_http_lua_socket_tcp_finalize_read_part(r, u);
    }

    return ngx_http_lua_socket_prepare_error_retvals(r, u, L, ft_type);
}