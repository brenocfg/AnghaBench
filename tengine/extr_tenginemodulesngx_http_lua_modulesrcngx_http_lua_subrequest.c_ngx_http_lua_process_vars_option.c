#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_8__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_7__ {int /*<<< orphan*/  len; int /*<<< orphan*/ * data; } ;
struct TYPE_9__ {TYPE_2__ value; TYPE_1__ key; } ;
typedef  TYPE_3__ ngx_keyval_t ;
struct TYPE_10__ {int /*<<< orphan*/  pool; } ;
typedef  TYPE_4__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  ngx_array_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ LUA_TSTRING ; 
 int /*<<< orphan*/  dd (char*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_next (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * ngx_array_create (int /*<<< orphan*/ ,int,int) ; 
 TYPE_3__* ngx_array_push (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
ngx_http_lua_process_vars_option(ngx_http_request_t *r, lua_State *L,
    int table, ngx_array_t **varsp)
{
    ngx_array_t         *vars;
    ngx_keyval_t        *var;

    if (table < 0) {
        table = lua_gettop(L) + table + 1;
    }

    vars = *varsp;

    if (vars == NULL) {

        vars = ngx_array_create(r->pool, 4, sizeof(ngx_keyval_t));
        if (vars == NULL) {
            dd("here");
            luaL_error(L, "no memory");
            return;
        }

        *varsp = vars;
    }

    lua_pushnil(L);
    while (lua_next(L, table) != 0) {

        if (lua_type(L, -2) != LUA_TSTRING) {
            luaL_error(L, "attempt to use a non-string key in the "
                       "\"vars\" option table");
            return;
        }

        if (!lua_isstring(L, -1)) {
            luaL_error(L, "attempt to use bad variable value type %s",
                       luaL_typename(L, -1));
            return;
        }

        var = ngx_array_push(vars);
        if (var == NULL) {
            dd("here");
            luaL_error(L, "no memory");
            return;
        }

        var->key.data = (u_char *) lua_tolstring(L, -2, &var->key.len);
        var->value.data = (u_char *) lua_tolstring(L, -1, &var->value.len);

        lua_pop(L, 1);
    }
}