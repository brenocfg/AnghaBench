#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_35__   TYPE_9__ ;
typedef  struct TYPE_34__   TYPE_8__ ;
typedef  struct TYPE_33__   TYPE_7__ ;
typedef  struct TYPE_32__   TYPE_6__ ;
typedef  struct TYPE_31__   TYPE_5__ ;
typedef  struct TYPE_30__   TYPE_4__ ;
typedef  struct TYPE_29__   TYPE_3__ ;
typedef  struct TYPE_28__   TYPE_2__ ;
typedef  struct TYPE_27__   TYPE_22__ ;
typedef  struct TYPE_26__   TYPE_20__ ;
typedef  struct TYPE_25__   TYPE_1__ ;
typedef  struct TYPE_24__   TYPE_10__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  scalar_t__ ngx_socket_t ;
typedef  scalar_t__ ngx_msec_t ;
struct TYPE_32__ {TYPE_5__* connection; int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; } ;
typedef  TYPE_6__ ngx_http_request_t ;
struct TYPE_28__ {int /*<<< orphan*/ * data; scalar_t__ len; } ;
struct TYPE_33__ {int co_ref; int /*<<< orphan*/ * pool; int /*<<< orphan*/ * co; TYPE_3__* vm_state; TYPE_2__ client_addr_text; int /*<<< orphan*/ * listening; TYPE_8__* lmcf; int /*<<< orphan*/  loc_conf; int /*<<< orphan*/  srv_conf; int /*<<< orphan*/  main_conf; scalar_t__ premature; scalar_t__ delay; } ;
typedef  TYPE_7__ ngx_http_lua_timer_ctx_t ;
struct TYPE_34__ {scalar_t__ pending_timers; scalar_t__ max_pending_timers; TYPE_20__* watcher; } ;
typedef  TYPE_8__ ngx_http_lua_main_conf_t ;
struct TYPE_35__ {TYPE_3__* vm_state; } ;
typedef  TYPE_9__ ngx_http_lua_ctx_t ;
typedef  int /*<<< orphan*/  ngx_http_core_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_http_connection_t ;
struct TYPE_24__ {int /*<<< orphan*/  log; TYPE_7__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_10__ ngx_event_t ;
typedef  int /*<<< orphan*/  ngx_connection_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_25__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_31__ {TYPE_1__ addr_text; int /*<<< orphan*/ * listening; int /*<<< orphan*/  log; } ;
struct TYPE_30__ {int /*<<< orphan*/  handler; } ;
struct TYPE_29__ {int /*<<< orphan*/  count; } ;
struct TYPE_27__ {int /*<<< orphan*/  log; int /*<<< orphan*/ ** files; } ;
struct TYPE_26__ {int idle; TYPE_8__* data; TYPE_4__* read; scalar_t__ fd; } ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  coroutines_key ; 
 int /*<<< orphan*/  dd (char*,int) ; 
 int /*<<< orphan*/  luaL_argcheck (int /*<<< orphan*/ *,int,int,char*) ; 
 int luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int luaL_ref (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_unref (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_iscfunction (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isfunction (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * lua_newthread (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawget (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfenv (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_xmove (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_add_timer (TYPE_10__*,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_alloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * ngx_create_pool (int,int /*<<< orphan*/ ) ; 
 TYPE_22__* ngx_cycle ; 
 int /*<<< orphan*/  ngx_destroy_pool (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_exiting ; 
 int /*<<< orphan*/  ngx_free (TYPE_10__*) ; 
 TYPE_20__* ngx_get_connection (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_9__* ngx_http_get_module_ctx (TYPE_6__*,int /*<<< orphan*/ ) ; 
 TYPE_8__* ngx_http_get_module_main_conf (TYPE_6__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_abort_pending_timers ; 
 int /*<<< orphan*/  ngx_http_lua_get_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_lua_vm (TYPE_6__*,TYPE_9__*) ; 
 TYPE_6__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 
 int /*<<< orphan*/  ngx_http_lua_probe_user_coroutine_create (TYPE_6__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_set_globals_table (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_timer_handler ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_debug2 (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_memzero (TYPE_10__*,int) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_timer_helper(lua_State *L, int every)
{
    int                      nargs, co_ref;
    u_char                  *p;
    lua_State               *vm;  /* the main thread */
    lua_State               *co;
    ngx_msec_t               delay;
    ngx_event_t             *ev = NULL;
    ngx_http_request_t      *r;
    ngx_connection_t        *saved_c = NULL;
    ngx_http_lua_ctx_t      *ctx;
#if 0
    ngx_http_connection_t   *hc;
#endif

    ngx_http_lua_timer_ctx_t      *tctx = NULL;
    ngx_http_lua_main_conf_t      *lmcf;
#if 0
    ngx_http_core_main_conf_t     *cmcf;
#endif

    nargs = lua_gettop(L);
    if (nargs < 2) {
        return luaL_error(L, "expecting at least 2 arguments but got %d",
                          nargs);
    }

    delay = (ngx_msec_t) (luaL_checknumber(L, 1) * 1000);

    if (every && delay == 0) {
        return luaL_error(L, "delay cannot be zero");
    }

    luaL_argcheck(L, lua_isfunction(L, 2) && !lua_iscfunction(L, 2), 2,
                  "Lua function expected");

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request");
    }

    ctx = ngx_http_get_module_ctx(r, ngx_http_lua_module);

    if (ngx_exiting && delay > 0) {
        lua_pushnil(L);
        lua_pushliteral(L, "process exiting");
        return 2;
    }

    lmcf = ngx_http_get_module_main_conf(r, ngx_http_lua_module);

    if (lmcf->pending_timers >= lmcf->max_pending_timers) {
        lua_pushnil(L);
        lua_pushliteral(L, "too many pending timers");
        return 2;
    }

    if (lmcf->watcher == NULL) {
        /* create the watcher fake connection */

        ngx_log_debug0(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                       "lua creating fake watcher connection");

        if (ngx_cycle->files) {
            saved_c = ngx_cycle->files[0];
        }

        lmcf->watcher = ngx_get_connection(0, ngx_cycle->log);

        if (ngx_cycle->files) {
            ngx_cycle->files[0] = saved_c;
        }

        if (lmcf->watcher == NULL) {
            return luaL_error(L, "no memory");
        }

        /* to work around the -1 check in ngx_worker_process_cycle: */
        lmcf->watcher->fd = (ngx_socket_t) -2;

        lmcf->watcher->idle = 1;
        lmcf->watcher->read->handler = ngx_http_lua_abort_pending_timers;
        lmcf->watcher->data = lmcf;
    }

    vm = ngx_http_lua_get_lua_vm(r, ctx);

    co = lua_newthread(vm);

    /* L stack: time func [args] */

    ngx_http_lua_probe_user_coroutine_create(r, L, co);

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

    /* L stack: time func [args] thread */
    /* vm stack: empty */

    lua_pushvalue(L, 2);    /* copy entry function to top of L*/

    /* L stack: time func [args] thread func */

    lua_xmove(L, co, 1);    /* move entry function from L to co */

    /* L stack: time func [args] thread */
    /* co stack: func */

#ifndef OPENRESTY_LUAJIT
    ngx_http_lua_get_globals_table(co);
    lua_setfenv(co, -2);
#endif

    /* co stack: func */

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);

    /* L stack: time func [args] thread coroutines */

    lua_pushvalue(L, -2);

    /* L stack: time func [args] thread coroutines thread */

    co_ref = luaL_ref(L, -2);
    lua_pop(L, 1);

    /* L stack: time func [args] thread */

    if (nargs > 2) {
        lua_pop(L, 1);  /* L stack: time func [args] */
        lua_xmove(L, co, nargs - 2);  /* L stack: time func */

        /* co stack: func [args] */
    }

    p = ngx_alloc(sizeof(ngx_event_t) + sizeof(ngx_http_lua_timer_ctx_t),
                  r->connection->log);
    if (p == NULL) {
        goto nomem;
    }

    ev = (ngx_event_t *) p;

    ngx_memzero(ev, sizeof(ngx_event_t));

    p += sizeof(ngx_event_t);

    tctx = (ngx_http_lua_timer_ctx_t *) p;

    tctx->delay = every ? delay : 0;

    tctx->premature = 0;
    tctx->co_ref = co_ref;
    tctx->co = co;
    tctx->main_conf = r->main_conf;
    tctx->srv_conf = r->srv_conf;
    tctx->loc_conf = r->loc_conf;
    tctx->lmcf = lmcf;

    tctx->pool = ngx_create_pool(128, ngx_cycle->log);
    if (tctx->pool == NULL) {
        goto nomem;
    }

    if (r->connection) {
        tctx->listening = r->connection->listening;

    } else {
        tctx->listening = NULL;
    }

    if (r->connection->addr_text.len) {
        tctx->client_addr_text.data = ngx_palloc(tctx->pool,
                                                 r->connection->addr_text.len);
        if (tctx->client_addr_text.data == NULL) {
            goto nomem;
        }

        ngx_memcpy(tctx->client_addr_text.data, r->connection->addr_text.data,
                   r->connection->addr_text.len);
        tctx->client_addr_text.len = r->connection->addr_text.len;

    } else {
        tctx->client_addr_text.len = 0;
        tctx->client_addr_text.data = NULL;
    }

    if (ctx && ctx->vm_state) {
        tctx->vm_state = ctx->vm_state;
        tctx->vm_state->count++;

    } else {
        tctx->vm_state = NULL;
    }

    ev->handler = ngx_http_lua_timer_handler;
    ev->data = tctx;
    ev->log = ngx_cycle->log;

    lmcf->pending_timers++;

    ngx_add_timer(ev, delay);

    ngx_log_debug2(NGX_LOG_DEBUG_HTTP, ngx_cycle->log, 0,
                   "created timer (co: %p delay: %M ms)", tctx->co, delay);

    lua_pushinteger(L, 1);
    return 1;

nomem:

    if (tctx && tctx->pool) {
        ngx_destroy_pool(tctx->pool);
    }

    if (ev) {
        ngx_free(ev);
    }

    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          coroutines_key));
    lua_rawget(L, LUA_REGISTRYINDEX);
    luaL_unref(L, -1, co_ref);

    return luaL_error(L, "no memory");
}