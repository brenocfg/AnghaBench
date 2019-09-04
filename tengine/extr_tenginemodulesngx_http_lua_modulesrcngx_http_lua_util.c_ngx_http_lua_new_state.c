#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_7__ {size_t len; scalar_t__ data; } ;
struct TYPE_6__ {size_t len; scalar_t__ data; } ;
struct TYPE_8__ {TYPE_2__ lua_cpath; TYPE_1__ lua_path; } ;
typedef  TYPE_3__ ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  ngx_cycle_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_DEBUG_HTTP ; 
 int /*<<< orphan*/  NGX_LOG_EMERG ; 
 int /*<<< orphan*/  dd (char*,char const*) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_istable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 char* lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_init_globals (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_init_registry (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_set_path (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,char*,char const*,char const*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_debug0 (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static lua_State *
ngx_http_lua_new_state(lua_State *parent_vm, ngx_cycle_t *cycle,
    ngx_http_lua_main_conf_t *lmcf, ngx_log_t *log)
{
    lua_State       *L;
    const char      *old_path;
    const char      *new_path;
    size_t           old_path_len;
    const char      *old_cpath;
    const char      *new_cpath;
    size_t           old_cpath_len;

    ngx_log_debug0(NGX_LOG_DEBUG_HTTP, log, 0, "lua creating new vm state");

    L = luaL_newstate();
    if (L == NULL) {
        return NULL;
    }

    luaL_openlibs(L);

    lua_getglobal(L, "package");

    if (!lua_istable(L, -1)) {
        ngx_log_error(NGX_LOG_EMERG, log, 0,
                      "the \"package\" table does not exist");
        return NULL;
    }

    if (parent_vm) {
        lua_getglobal(parent_vm, "package");
        lua_getfield(parent_vm, -1, "path");
        old_path = lua_tolstring(parent_vm, -1, &old_path_len);
        lua_pop(parent_vm, 1);

        lua_pushlstring(L, old_path, old_path_len);
        lua_setfield(L, -2, "path");

        lua_getfield(parent_vm, -1, "cpath");
        old_path = lua_tolstring(parent_vm, -1, &old_path_len);
        lua_pop(parent_vm, 2);

        lua_pushlstring(L, old_path, old_path_len);
        lua_setfield(L, -2, "cpath");

    } else {
#ifdef LUA_DEFAULT_PATH
#   define LUA_DEFAULT_PATH_LEN (sizeof(LUA_DEFAULT_PATH) - 1)
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0,
                       "lua prepending default package.path with %s",
                       LUA_DEFAULT_PATH);

        lua_pushliteral(L, LUA_DEFAULT_PATH ";"); /* package default */
        lua_getfield(L, -2, "path"); /* package default old */
        old_path = lua_tolstring(L, -1, &old_path_len);
        lua_concat(L, 2); /* package new */
        lua_setfield(L, -2, "path"); /* package */
#endif

#ifdef LUA_DEFAULT_CPATH
#   define LUA_DEFAULT_CPATH_LEN (sizeof(LUA_DEFAULT_CPATH) - 1)
        ngx_log_debug1(NGX_LOG_DEBUG_HTTP, log, 0,
                       "lua prepending default package.cpath with %s",
                       LUA_DEFAULT_CPATH);

        lua_pushliteral(L, LUA_DEFAULT_CPATH ";"); /* package default */
        lua_getfield(L, -2, "cpath"); /* package default old */
        old_cpath = lua_tolstring(L, -1, &old_cpath_len);
        lua_concat(L, 2); /* package new */
        lua_setfield(L, -2, "cpath"); /* package */
#endif

        if (lmcf->lua_path.len != 0) {
            lua_getfield(L, -1, "path"); /* get original package.path */
            old_path = lua_tolstring(L, -1, &old_path_len);

            dd("old path: %s", old_path);

            lua_pushlstring(L, (char *) lmcf->lua_path.data,
                            lmcf->lua_path.len);
            new_path = lua_tostring(L, -1);

            ngx_http_lua_set_path(cycle, L, -3, "path", new_path, old_path,
                                  log);

            lua_pop(L, 2);
        }

        if (lmcf->lua_cpath.len != 0) {
            lua_getfield(L, -1, "cpath"); /* get original package.cpath */
            old_cpath = lua_tolstring(L, -1, &old_cpath_len);

            dd("old cpath: %s", old_cpath);

            lua_pushlstring(L, (char *) lmcf->lua_cpath.data,
                            lmcf->lua_cpath.len);
            new_cpath = lua_tostring(L, -1);

            ngx_http_lua_set_path(cycle, L, -3, "cpath", new_cpath, old_cpath,
                                  log);


            lua_pop(L, 2);
        }
    }

    lua_pop(L, 1); /* remove the "package" table */

    ngx_http_lua_init_registry(L, log);
    ngx_http_lua_init_globals(L, cycle, lmcf, log);

    return L;
}