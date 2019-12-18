#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
typedef  int ngx_uint_t ;
struct TYPE_9__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_1__ ngx_str_t ;
struct TYPE_10__ {scalar_t__ len; scalar_t__ data; scalar_t__ not_found; } ;
typedef  TYPE_2__ ngx_http_variable_value_t ;
struct TYPE_11__ {int ncaptures; int* captures; int /*<<< orphan*/ * captures_data; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  scalar_t__ LUA_NUMBER ;

/* Variables and functions */
 scalar_t__ LUA_TNUMBER ; 
 scalar_t__ LUA_TSTRING ; 
 int /*<<< orphan*/  dd (char*,int,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * lua_newuserdata (int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/  lua_pushlstring (int /*<<< orphan*/ *,char const*,size_t) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_type (int /*<<< orphan*/ *,int) ; 
 int ngx_hash_strlow (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 TYPE_2__* ngx_http_get_variable (TYPE_3__*,TYPE_1__*,int) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_var_get(lua_State *L)
{
    ngx_http_request_t          *r;
    u_char                      *p, *lowcase;
    size_t                       len;
    ngx_uint_t                   hash;
    ngx_str_t                    name;
    ngx_http_variable_value_t   *vv;

#if (NGX_PCRE)
    u_char                      *val;
    ngx_uint_t                   n;
    LUA_NUMBER                   index;
    int                         *cap;
#endif

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    ngx_http_lua_check_fake_request(L, r);

#if (NGX_PCRE)
    if (lua_type(L, -1) == LUA_TNUMBER) {
        /* it is a regex capturing variable */

        index = lua_tonumber(L, -1);

        if (index <= 0) {
            lua_pushnil(L);
            return 1;
        }

        n = (ngx_uint_t) index * 2;

        dd("n = %d, ncaptures = %d", (int) n, (int) r->ncaptures);

        if (r->captures == NULL
            || r->captures_data == NULL
            || n >= r->ncaptures)
        {
            lua_pushnil(L);
            return 1;
        }

        /* n >= 0 && n < r->ncaptures */

        cap = r->captures;

        p = r->captures_data;

        val = &p[cap[n]];

        lua_pushlstring(L, (const char *) val, (size_t) (cap[n + 1] - cap[n]));

        return 1;
    }
#endif

    if (lua_type(L, -1) != LUA_TSTRING) {
        return luaL_error(L, "bad variable name");
    }

    p = (u_char *) lua_tolstring(L, -1, &len);

    lowcase = lua_newuserdata(L, len);

    hash = ngx_hash_strlow(lowcase, p, len);

    name.len = len;
    name.data = lowcase;

    vv = ngx_http_get_variable(r, &name, hash);

    if (vv == NULL || vv->not_found) {
        lua_pushnil(L);
        return 1;
    }

    lua_pushlstring(L, (const char *) vv->data, (size_t) vv->len);
    return 1;
}