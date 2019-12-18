#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u_char ;
struct TYPE_5__ {scalar_t__ len; int /*<<< orphan*/  data; } ;
struct TYPE_6__ {int /*<<< orphan*/  pool; TYPE_1__ args; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int NGX_HTTP_LUA_MAX_ARGS ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_2__*) ; 
 TYPE_2__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int ngx_http_lua_parse_args (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  ngx_pfree (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_get_uri_args(lua_State *L)
{
    ngx_http_request_t          *r;
    u_char                      *buf;
    u_char                      *last;
    int                          retval;
    int                          n;
    int                          max;

    n = lua_gettop(L);

    if (n != 0 && n != 1) {
        return luaL_error(L, "expecting 0 or 1 arguments but seen %d", n);
    }

    if (n == 1) {
        max = luaL_checkinteger(L, 1);
        lua_pop(L, 1);

    } else {
        max = NGX_HTTP_LUA_MAX_ARGS;
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    ngx_http_lua_check_fake_request(L, r);

    if (r->args.len == 0) {
        lua_createtable(L, 0, 0);
        return 1;
    }

    /* we copy r->args over to buf to simplify
     * unescaping query arg keys and values */

    buf = ngx_palloc(r->pool, r->args.len);
    if (buf == NULL) {
        return luaL_error(L, "no memory");
    }

    lua_createtable(L, 0, 4);

    ngx_memcpy(buf, r->args.data, r->args.len);

    last = buf + r->args.len;

    retval = ngx_http_lua_parse_args(L, buf, last, max);

    ngx_pfree(r->pool, buf);

    return retval;
}