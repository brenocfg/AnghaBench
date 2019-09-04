#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ngx_uint_t ;
typedef  int /*<<< orphan*/  ngx_log_t ;
struct TYPE_6__ {TYPE_1__* connection; } ;
typedef  TYPE_2__ ngx_http_request_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {int /*<<< orphan*/ * log; } ;
struct TYPE_5__ {int /*<<< orphan*/ * log; } ;

/* Variables and functions */
 int NGX_LOG_DEBUG ; 
 int NGX_LOG_STDERR ; 
 int log_wrapper (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int luaL_argerror (int /*<<< orphan*/ *,int,char const*) ; 
 int luaL_checkint (int /*<<< orphan*/ *,int) ; 
 char* lua_pushfstring (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_remove (int /*<<< orphan*/ *,int) ; 
 TYPE_4__* ngx_cycle ; 
 TYPE_2__* ngx_http_lua_get_req (int /*<<< orphan*/ *) ; 

int
ngx_http_lua_ngx_log(lua_State *L)
{
    ngx_log_t                   *log;
    ngx_http_request_t          *r;
    const char                  *msg;
    int                          level;

    r = ngx_http_lua_get_req(L);

    if (r && r->connection && r->connection->log) {
        log = r->connection->log;

    } else {
        log = ngx_cycle->log;
    }

    level = luaL_checkint(L, 1);
    if (level < NGX_LOG_STDERR || level > NGX_LOG_DEBUG) {
        msg = lua_pushfstring(L, "bad log level: %d", level);
        return luaL_argerror(L, 1, msg);
    }

    /* remove log-level param from stack */
    lua_remove(L, 1);

    return log_wrapper(log, "[lua] ", (ngx_uint_t) level, L);
}