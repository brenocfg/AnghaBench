#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ NGX_ERROR ; 
 scalar_t__ NGX_HTTP_SPECIAL_RESPONSE ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 scalar_t__ ngx_http_discard_request_body (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_req_discard_body(lua_State *L)
{
    ngx_http_request_t          *r;
    ngx_int_t                    rc;
    int                          n;

    n = lua_gettop(L);

    if (n != 0) {
        return luaL_error(L, "expecting 0 arguments but seen %d", n);
    }

    r = ngx_http_lua_get_req(L);
    if (r == NULL) {
        return luaL_error(L, "request object not found");
    }

    ngx_http_lua_check_fake_request(L, r);

    rc = ngx_http_discard_request_body(r);

    if (rc == NGX_ERROR || rc >= NGX_HTTP_SPECIAL_RESPONSE) {
        return luaL_error(L, "failed to discard request body");
    }

    return 0;
}