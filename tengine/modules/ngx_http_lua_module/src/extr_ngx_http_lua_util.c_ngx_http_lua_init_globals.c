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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  ngx_http_lua_inject_ndk_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_ngx_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static void
ngx_http_lua_init_globals(lua_State *L, ngx_cycle_t *cycle,
    ngx_http_lua_main_conf_t *lmcf, ngx_log_t *log)
{
    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, log, 0,
                   "lua initializing lua globals");

#if defined(NDK) && NDK
    ngx_http_lua_inject_ndk_api(L);
#endif /* defined(NDK) && NDK */

    ngx_http_lua_inject_ngx_api(L, lmcf, log);
}