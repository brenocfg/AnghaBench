#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_19__   TYPE_5__ ;
typedef  struct TYPE_18__   TYPE_4__ ;
typedef  struct TYPE_17__   TYPE_3__ ;
typedef  struct TYPE_16__   TYPE_2__ ;
typedef  struct TYPE_15__   TYPE_1__ ;
typedef  struct TYPE_14__   TYPE_12__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_15__ {int len; TYPE_3__* data; } ;
struct TYPE_17__ {int co_ref; int /*<<< orphan*/ * pool; int /*<<< orphan*/  delay; int /*<<< orphan*/ * co; TYPE_2__* vm_state; TYPE_1__ client_addr_text; TYPE_4__* lmcf; } ;
typedef  TYPE_3__ ngx_http_lua_timer_ctx_t ;
struct TYPE_18__ {int /*<<< orphan*/  pending_timers; int /*<<< orphan*/ * lua; } ;
typedef  TYPE_4__ ngx_http_lua_main_conf_t ;
struct TYPE_19__ {int /*<<< orphan*/  log; TYPE_3__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_5__ ngx_event_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_16__ {int /*<<< orphan*/  count; int /*<<< orphan*/ * vm; } ;
struct TYPE_14__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  coroutines_key ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 int luaL_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * lua_newthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_5__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 TYPE_12__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_free (TYPE_5__*) ; 
 int /*<<< orphan*/  ngx_http_lua_get_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_set_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_timer_handler ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_memcpy (TYPE_3__*,TYPE_3__*,int) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_5__*,int) ; 
 TYPE_3__* ngx_palloc (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static ngx_int_t
ngx_http_lua_timer_copy(ngx_http_lua_timer_ctx_t *old_tctx)
{
    int                          nargs, co_ref, i;
    u_char                      *p;
    lua_State                   *vm;  /* the main thread */
    lua_State                   *co;
    lua_State                   *L;
    ngx_event_t                 *ev = NULL;
    ngx_http_lua_timer_ctx_t    *tctx = NULL;
    ngx_http_lua_main_conf_t    *lmcf;

    /* L stack: func [args] */
    L = old_tctx->co;

    lmcf = old_tctx->lmcf;

    vm = old_tctx->vm_state ? old_tctx->vm_state->vm : lmcf->lua;

    co = lua_newthread(vm);

#ifndef OPENRESTY_LUAJIT
    lua_createtable(co, 0, 0);  /* the new globals table */

    /* co stack: global_tb */

    lua_createtable(co, 0, 1);  /* the metatable */
    ngx_http_lua_get_globals_table(co);
    lua_setfield(co, -2, "__index");
    lua_setmetatable(co, -2);

    /* co stack: global_tb */

    ngx_http_lua_set_globals_table(co);
#endif

    /* co stack: <empty> */

    dd("stack top: %d", lua_gettop(L));

    lua_xmove(vm, L, 1);    /* move coroutine from main thread to L */

    /* L stack: func [args] thread */
    /* vm stack: empty */

    lua_pushvalue(L, 1);    /* copy entry function to top of L*/

    /* L stack: func [args] thread func */

    lua_xmove(L, co, 1);    /* move entry function from L to co */

    /* L stack: func [args] thread */
    /* co stack: func */

#ifndef OPENRESTY_LUAJIT
    ngx_http_lua_get_globals_table(co);
    lua_setfenv(co, -2);
#endif

    /* co stack: func */

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* L stack: func [args] thread coroutines */

    lua_pushvalue(L, -2);

    /* L stack: func [args] thread coroutines thread */

    co_ref = luaL_ref(L, -2);
    lua_pop(L, 2);

    /* L stack: func [args] */

    nargs = lua_gettop(L);
    if (nargs > 1) {
        for (i = 2; i <= nargs; i++) {
            lua_pushvalue(L, i);
        }

        /* L stack: func [args] [args] */

        lua_xmove(L, co, nargs - 1);

        /* L stack: func [args] */
        /* co stack: func [args] */
    }

    p = ngx_alloc(sizeof(ngx_event_t) + sizeof(ngx_http_lua_timer_ctx_t),
                  ngx_cycle->log);
    if (p == NULL) {
        goto nomem;
    }

    ev = (ngx_event_t *) p;

    ngx_memzero(ev, sizeof(ngx_event_t));

    p += sizeof(ngx_event_t);

    tctx = (ngx_http_lua_timer_ctx_t *) p;

    ngx_memcpy(tctx, old_tctx, sizeof(ngx_http_lua_timer_ctx_t));

    tctx->co_ref = co_ref;
    tctx->co = co;

    tctx->pool = ngx_create_pool(128, ngx_cycle->log);
    if (tctx->pool == NULL) {
        goto nomem;
    }

    if (tctx->client_addr_text.len) {
        tctx->client_addr_text.data = ngx_palloc(tctx->pool,
                                                 tctx->client_addr_text.len);
        if (tctx->client_addr_text.data == NULL) {
            goto nomem;
        }

        ngx_memcpy(tctx->client_addr_text.data, old_tctx->client_addr_text.data,
                   tctx->client_addr_text.len);
    }

    if (tctx->vm_state) {
        tctx->vm_state->count++;
    }

    ev->handler = ngx_http_lua_timer_handler;
    ev->data = tctx;
    ev->log = ngx_cycle->log;

    lmcf->pending_timers++;

    ngx_add_timer(ev, tctx->delay);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "created next timer (co: %p delay: %M ms)", tctx->co,
                   tctx->delay);

    return NGX_OK;

nomem:

    if (tctx && tctx->pool) {
        ngx_destroy_pool(tctx->pool);
    }

    if (ev) {
        ngx_free(ev);
    }

    /* L stack: func [args] */

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    luaL_unref(L, -1, co_ref);

    /* L stack: func [args] coroutines */

    lua_pop(L, 1);

    return NGX_ERROR;
}