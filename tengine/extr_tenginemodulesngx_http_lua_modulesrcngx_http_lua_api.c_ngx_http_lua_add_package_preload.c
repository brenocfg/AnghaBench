#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int /*<<< orphan*/  ngx_int_t ;
struct TYPE_8__ {int /*<<< orphan*/  loader; int /*<<< orphan*/ * package; } ;
typedef  TYPE_1__ ngx_http_lua_preload_hook_t ;
struct TYPE_9__ {int /*<<< orphan*/ * preload_hooks; int /*<<< orphan*/ * lua; } ;
typedef  TYPE_2__ ngx_http_lua_main_conf_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_CFunction ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_ERROR ; 
 int /*<<< orphan*/  NGX_OK ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char const*) ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_1__* ngx_array_push (int /*<<< orphan*/ *) ; 
 TYPE_2__* ngx_http_conf_get_module_main_conf (TYPE_3__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_module ; 

ngx_int_t
ngx_http_lua_add_package_preload(ngx_conf_t *cf, const char *package,
    lua_CFunction func)
{
    lua_State                     *L;
    ngx_http_lua_main_conf_t      *lmcf;
    ngx_http_lua_preload_hook_t   *hook;

    lmcf = ngx_http_conf_get_module_main_conf(cf, ngx_http_lua_module);

    L = lmcf->lua;

    if (L) {
        lua_getglobal(L, "package");
        lua_getfield(L, -1, "preload");
        lua_pushcfunction(L, func);
        lua_setfield(L, -2, package);
        lua_pop(L, 2);
    }

    /* we always register preload_hooks since we always create new Lua VMs
     * when lua code cache is off. */

    if (lmcf->preload_hooks == NULL) {
        lmcf->preload_hooks =
            ngx_array_create(cf->pool, 4,
                             sizeof(ngx_http_lua_preload_hook_t));

        if (lmcf->preload_hooks == NULL) {
            return NGX_ERROR;
        }
    }

    hook = ngx_array_push(lmcf->preload_hooks);
    if (hook == NULL) {
        return NGX_ERROR;
    }

    hook->package = (u_char *) package;
    hook->loader = func;

    return NGX_OK;
}