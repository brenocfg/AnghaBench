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
typedef  int /*<<< orphan*/  ngx_log_t ;
typedef  int /*<<< orphan*/  ngx_http_lua_main_conf_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  NGX_LOG_ERR ; 
 int luaL_loadbuffer (int /*<<< orphan*/ *,char const*,int,char*) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int lua_pcall (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  ngx_http_lua_create_headers_metatable (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_get_raw_phase_context ; 
 int /*<<< orphan*/  ngx_http_lua_inject_arg_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_config_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_control_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_core_consts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_coroutine_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_http_consts (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_log_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_misc_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_output_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_phase_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_regex_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_req_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_resp_header_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_shdict_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_sleep_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_socket_tcp_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_socket_udp_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_string_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_subrequest_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_time_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_timer_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_uthread_api (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_variable_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_http_lua_inject_worker_api (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
ngx_http_lua_inject_ngx_api(lua_State *L, ngx_http_lua_main_conf_t *lmcf,
    ngx_log_t *log)
{
    lua_createtable(L, 0 /* narr */, 117 /* nrec */);    /* ngx.* */

    lua_pushcfunction(L, ngx_http_lua_get_raw_phase_context);
    lua_setfield(L, -2, "_phase_ctx");

    ngx_http_lua_inject_arg_api(L);

    ngx_http_lua_inject_http_consts(L);
    ngx_http_lua_inject_core_consts(L);

    ngx_http_lua_inject_log_api(L);
    ngx_http_lua_inject_output_api(L);
    ngx_http_lua_inject_time_api(L);
    ngx_http_lua_inject_string_api(L);
    ngx_http_lua_inject_control_api(log, L);
    ngx_http_lua_inject_subrequest_api(L);
    ngx_http_lua_inject_sleep_api(L);
    ngx_http_lua_inject_phase_api(L);

#if (NGX_PCRE)
    ngx_http_lua_inject_regex_api(L);
#endif

    ngx_http_lua_inject_req_api(log, L);
    ngx_http_lua_inject_resp_header_api(L);
    ngx_http_lua_create_headers_metatable(log, L);
    ngx_http_lua_inject_variable_api(L);
    ngx_http_lua_inject_shdict_api(lmcf, L);
    ngx_http_lua_inject_socket_tcp_api(log, L);
    ngx_http_lua_inject_socket_udp_api(log, L);
    ngx_http_lua_inject_uthread_api(log, L);
    ngx_http_lua_inject_timer_api(L);
    ngx_http_lua_inject_config_api(L);
    ngx_http_lua_inject_worker_api(L);

    ngx_http_lua_inject_misc_api(L);

    lua_getglobal(L, "package"); /* ngx package */
    lua_getfield(L, -1, "loaded"); /* ngx package loaded */
    lua_pushvalue(L, -3); /* ngx package loaded ngx */
    lua_setfield(L, -2, "ngx"); /* ngx package loaded */
    lua_pop(L, 2);

    lua_setglobal(L, "ngx");

    ngx_http_lua_inject_coroutine_api(log, L);

#ifdef OPENRESTY_LUAJIT
    {
        int         rc;

        const char buf[] =
            "local ngx_log = ngx.log\n"
            "local ngx_WARN = ngx.WARN\n"
            "local tostring = tostring\n"
            "local ngx_get_phase = ngx.get_phase\n"
            "local traceback = require 'debug'.traceback\n"
            "local function newindex(table, key, value)\n"
                "rawset(table, key, value)\n"
                "local phase = ngx_get_phase()\n"
                "if phase == 'init_worker' or phase == 'init' then\n"
                    "return\n"
                "end\n"
                "ngx_log(ngx_WARN, 'writing a global lua variable "
                         "(\\'', tostring(key), '\\') which may lead to "
                         "race conditions between concurrent requests, so "
                         "prefer the use of \\'local\\' variables', "
                         "traceback('', 2))\n"
            "end\n"
            "setmetatable(_G, { __newindex = newindex })\n"
            ;

        rc = luaL_loadbuffer(L, buf, sizeof(buf) - 1, "=_G write guard");

        if (rc != 0) {
            ngx_log_error(NGX_LOG_ERR, log, 0,
                          "failed to load Lua code (%i): %s",
                          rc, lua_tostring(L, -1));

            lua_pop(L, 1);
            return;
        }

        rc = lua_pcall(L, 0, 0, 0);
        if (rc != 0) {
            ngx_log_error(NGX_LOG_ERR, log, 0,
                          "failed to run Lua code (%i): %s",
                          rc, lua_tostring(L, -1));
            lua_pop(L, 1);
        }
    }
#endif
}