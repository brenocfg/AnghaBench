#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * request; } ;
typedef  TYPE_1__ ngx_http_lua_socket_udp_upstream_t ;
struct TYPE_5__ {TYPE_1__* data; } ;
typedef  TYPE_2__ ngx_http_lua_co_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  ngx_http_lua_socket_udp_finalize (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static void
ngx_http_lua_udp_socket_cleanup(void *data)
{
    ngx_http_lua_socket_udp_upstream_t      *u;
    ngx_http_lua_co_ctx_t                   *coctx = data;

    u = coctx->data;
    if (u == NULL) {
        return;
    }

    if (u->request == NULL) {
        return;
    }

    ngx_http_lua_socket_udp_finalize(u->request, u);
}