#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_pool_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {int /*<<< orphan*/  pool; } ;

/* Variables and functions */
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_insert (int /*<<< orphan*/ *,int) ; 
 int lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 TYPE_1__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_http_lua_pcre_malloc_done (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_pcre_malloc_init (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_traceback ; 

int
ngx_http_lua_do_call(ngx_log_t *log, lua_State *L)
{
    int                 status, base;
#if (NGX_PCRE)
    ngx_pool_t         *old_pool;
#endif

    base = lua_gettop(L);  /* function index */
    lua_pushcfunction(L, ngx_http_lua_traceback);  /* push traceback function */
    lua_insert(L, base);  /* put it under chunk and args */

#if (NGX_PCRE)
    old_pool = ngx_http_lua_pcre_malloc_init(ngx_cycle->pool);
#endif

    status = lua_pcall(L, 0, 0, base);

#if (NGX_PCRE)
    ngx_http_lua_pcre_malloc_done(old_pool);
#endif

    lua_remove(L, base);

    return status;
}