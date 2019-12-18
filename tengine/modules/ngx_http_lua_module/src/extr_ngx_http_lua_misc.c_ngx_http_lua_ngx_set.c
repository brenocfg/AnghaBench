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
typedef  int ngx_uint_t ;
struct TYPE_10__ {scalar_t__ len; } ;
struct TYPE_8__ {int status; TYPE_4__ status_line; } ;
struct TYPE_9__ {TYPE_2__ headers_out; scalar_t__ err_status; TYPE_1__* connection; scalar_t__ header_sent; } ;
typedef  TYPE_3__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/  log; } ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 scalar_t__ luaL_checklstring (int /*<<< orphan*/ *,int,size_t*) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_check_fake_request (int /*<<< orphan*/ *,TYPE_3__*) ; 
 TYPE_3__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 
 int ngx_http_lua_ngx_set_ctx (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  ngx_str_set (TYPE_4__*,char*) ; 
 scalar_t__ ngx_strncmp (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static int
ngx_http_lua_ngx_set(lua_State *L)
{
    ngx_http_request_t          *r;
    u_char                      *p;
    size_t                       len;

    /* we skip the first argument that is the table */
    p = (u_char *) luaL_checklstring(L, 2, &len);

    if (len == sizeof("status") - 1
        && ngx_strncmp(p, "status", sizeof("status") - 1) == 0)
    {
        r = ngx_http_lua_get_req(L);
        if (r == NULL) {
            return luaL_error(L, "no request object found");
        }

        if (r->header_sent) {
            ngx_log_error(NGX_LOG_ERR, r->connection->log, 0,
                          "attempt to set ngx.status after sending out "
                          "response headers");
            return 0;
        }

        if (r->err_status) {
            r->err_status = 0;
        }

        ngx_http_lua_check_fake_request(L, r);

        /* get the value */
        r->headers_out.status = (ngx_uint_t) luaL_checknumber(L, 3);

        if (r->headers_out.status == 101) {
            /*
             * XXX work-around a bug in the Nginx core that 101 does
             * not have a default status line
             */

            ngx_str_set(&r->headers_out.status_line, "101 Switching Protocols");

        } else {
            r->headers_out.status_line.len = 0;
        }

        return 0;
    }

    if (len == sizeof("ctx") - 1
        && ngx_strncmp(p, "ctx", sizeof("ctx") - 1) == 0)
    {
        r = ngx_http_lua_get_req(L);
        if (r == NULL) {
            return luaL_error(L, "no request object found");
        }

        return ngx_http_lua_ngx_set_ctx(L);
    }

    lua_rawset(L, -3);
    return 0;
}