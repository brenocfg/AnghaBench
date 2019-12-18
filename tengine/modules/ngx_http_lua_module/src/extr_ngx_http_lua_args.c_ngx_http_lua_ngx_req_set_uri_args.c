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
struct TYPE_9__ {size_t len; int /*<<< orphan*/ * data; } ;
typedef  TYPE_2__ ngx_str_t ;
struct TYPE_8__ {size_t len; int /*<<< orphan*/ * data; } ;
struct TYPE_10__ {scalar_t__ valid_unparsed_uri; TYPE_1__ args; int /*<<< orphan*/  pool; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TNUMBER 130 
#define  LUA_TSTRING 129 
#define  LUA_TTABLE 128 
 int /*<<< orphan*/  dd (char*,int,int /*<<< orphan*/ *) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char const*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  luaL_typename (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_tolstring (int /*<<< orphan*/ *,int,size_t*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_process_args_option (TYPE_3__*,int /*<<< orphan*/ *,int,TYPE_2__*) ; 
 int /*<<< orphan*/  ngx_memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,size_t) ; 
 int /*<<< orphan*/ * ngx_palloc (int /*<<< orphan*/ ,size_t) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_set_uri_args(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_str_t                    args;
    const char                  *msg;
    size_t                       len;
    u_char                      *p;

    if (lua_gettop(L) != 1) {
        return luaL_error(L, "expecting 1 argument but seen %d",
                          lua_gettop(L));
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "no request object found");
    }

    ngx_http_lua_check_fake_request(L, r);

    switch (lua_type(L, 1)) {
    case LUA_TNUMBER:
    case LUA_TSTRING:
        p = (u_char *) lua_tolstring(L, 1, &len);

        args.data = ngx_palloc(r->pool, len);
        if (args.data == NULL) {
            return luaL_error(L, "no memory");
        }

        ngx_memcpy(args.data, p, len);

        args.len = len;
        break;

    case LUA_TTABLE:
        ngx_http_lua_process_args_option(r, L, 1, &args);

        dd("args: %.*s", (int) args.len, args.data);

        break;

    default:
        msg = lua_pushfstring(L, "string, number, or table expected, "
                              "but got %s", luaL_typename(L, 2));
        return luaL_argerror(L, 1, msg);
    }

    dd("args: %.*s", (int) args.len, args.data);

    r->args.data = args.data;
    r->args.len = args.len;

    r->valid_unparsed_uri = 0;

    return 0;
}