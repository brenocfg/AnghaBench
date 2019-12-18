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
typedef  int /*<<< orphan*/  ngx_http_lua_socket_pool_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ * lua_touserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_shutdown_pool_helper (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_socket_shutdown_pool(lua_State *L)
{
    ngx_http_lua_socket_pool_t          *spool;

    spool = lua_touserdata(L, 1);

    if (spool != NULL) {
        ngx_http_lua_socket_shutdown_pool_helper(spool);
    }

    return 0;
}