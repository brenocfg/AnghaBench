#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_5__ ;
typedef  struct TYPE_14__   TYPE_4__ ;
typedef  struct TYPE_13__   TYPE_3__ ;
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_pool_t ;
struct TYPE_12__ {TYPE_3__* data; int /*<<< orphan*/  handler; } ;
typedef  TYPE_2__ ngx_pool_cleanup_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_13__ {int count; int /*<<< orphan*/ * vm; } ;
typedef  TYPE_3__ ngx_http_lua_vm_state_t ;
struct TYPE_14__ {scalar_t__ package; int /*<<< orphan*/  loader; } ;
typedef  TYPE_4__ ngx_http_lua_preload_hook_t ;
struct TYPE_15__ {TYPE_1__* preload_hooks; TYPE_2__* vm_cleanup; } ;
typedef  TYPE_5__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_11__ {size_t nelts; TYPE_4__* elts; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  luaopen_ffi (int /*<<< orphan*/ *) ; 
 TYPE_3__* ngx_alloc (int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_cleanup_vm ; 
 int /*<<< orphan*/ * ngx_http_lua_new_state (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_probe_register_preload_package (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  ngx_log_debug1 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_pool_cleanup_add (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

lua_State *
ngx_http_lua_init_vm(lua_State *parent_vm, ngx_cycle_t *cycle,
    ngx_pool_t *pool, ngx_http_lua_main_conf_t *lmcf, ngx_log_t *log,
    ngx_pool_cleanup_t **pcln)
{
    lua_State                       *L;
    ngx_uint_t                       i;
    ngx_pool_cleanup_t              *cln;
    ngx_http_lua_preload_hook_t     *hook;
    ngx_http_lua_vm_state_t         *state;

    cln = ngx_pool_cleanup_add(pool, 0);
    if (cln == NULL) {
        return NULL;
    }

    /* create new Lua VM instance */
    L = ngx_http_lua_new_state(parent_vm, cycle, lmcf, log);
    if (L == NULL) {
        return NULL;
    }

    ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0, "lua initialize the "
                   "global Lua VM %p", L);

    /* register cleanup handler for Lua VM */
    cln->handler = ngx_http_lua_cleanup_vm;

    state = ngx_alloc(sizeof(ngx_http_lua_vm_state_t), log);
    if (state == NULL) {
        return NULL;
    }
    state->vm = L;
    state->count = 1;

    cln->data = state;

    if (lmcf->vm_cleanup == NULL) {
        /* this assignment will happen only once,
         * and also only for the main Lua VM */
        lmcf->vm_cleanup = cln;
    }

    if (pcln) {
        *pcln = cln;
    }

#ifdef OPENRESTY_LUAJIT
    /* load FFI library first since cdata needs it */
    luaopen_ffi(L);
#endif

    if (lmcf->preload_hooks) {

        /* register the 3rd-party module's preload hooks */

        lua_getglobal(L, "package");
        lua_getfield(L, -1, "preload");

        hook = lmcf->preload_hooks->elts;

        for (i = 0; i < lmcf->preload_hooks->nelts; i++) {

            ngx_http_lua_probe_register_preload_package(L, hook[i].package);

            lua_pushcfunction(L, hook[i].loader);
            lua_setfield(L, -2, (char *) hook[i].package);
        }

        lua_pop(L, 2);
    }

    return L;
}