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
typedef  scalar_t__ ngx_int_t ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  NGX_LOG_CRIT ; 
 scalar_t__ NGX_OK ; 
 int /*<<< orphan*/  downstream_udata_metatable_key ; 
 scalar_t__ luaL_loadbuffer (int /*<<< orphan*/ *,char const*,int,char*) ; 
 int /*<<< orphan*/  lua_createtable (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_rawset (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  ngx_http_lua_lightudata_mask (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ngx_http_lua_socket_cleanup_compiled_pattern ; 
 int /*<<< orphan*/  ngx_http_lua_socket_downstream_destroy ; 
 int /*<<< orphan*/  ngx_http_lua_socket_shutdown_pool ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_close ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_connect ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_getreusedtimes ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_receive ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_receiveany ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_receiveuntil ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_send ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_setkeepalive ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_setoption ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_settimeout ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_settimeouts ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_sslhandshake ; 
 int /*<<< orphan*/  ngx_http_lua_socket_tcp_upstream_destroy ; 
 int /*<<< orphan*/  ngx_http_lua_ssl_free_session ; 
 int /*<<< orphan*/  ngx_log_error (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,scalar_t__) ; 
 int /*<<< orphan*/  pattern_udata_metatable_key ; 
 int /*<<< orphan*/  pool_udata_metatable_key ; 
 int /*<<< orphan*/  raw_req_socket_metatable_key ; 
 int /*<<< orphan*/  req_socket_metatable_key ; 
 int /*<<< orphan*/  ssl_session_metatable_key ; 
 int /*<<< orphan*/  tcp_socket_metatable_key ; 
 int /*<<< orphan*/  upstream_udata_metatable_key ; 

void
ngx_http_lua_inject_socket_tcp_api(ngx_log_t *log, lua_State *L)
{
    ngx_int_t         rc;

    lua_createtable(L, 0, 4 /* nrec */);    /* ngx.socket */

    lua_pushcfunction(L, ngx_http_lua_socket_tcp);
    lua_pushvalue(L, -1);
    lua_setfield(L, -3, "tcp");
    lua_setfield(L, -2, "stream");

    {
        const char  buf[] = "local sock = ngx.socket.tcp()"
                            " local ok, err = sock:connect(...)"
                            " if ok then return sock else return nil, err end";

        rc = luaL_loadbuffer(L, buf, sizeof(buf) - 1, "=ngx.socket.connect");
    }

    if (rc != NGX_OK) {
        ngx_log_error(NGX_LOG_CRIT, log, 0,
                      "failed to load Lua code for ngx.socket.connect(): %i",
                      rc);

    } else {
        lua_setfield(L, -2, "connect");
    }

    lua_setfield(L, -2, "socket");

    /* {{{req socket object metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          req_socket_metatable_key));
    lua_createtable(L, 0 /* narr */, 5 /* nrec */);

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receive);
    lua_setfield(L, -2, "receive");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receiveuntil);
    lua_setfield(L, -2, "receiveuntil");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_settimeout);
    lua_setfield(L, -2, "settimeout"); /* ngx socket mt */

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_settimeouts);
    lua_setfield(L, -2, "settimeouts"); /* ngx socket mt */

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* {{{raw req socket object metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          raw_req_socket_metatable_key));
    lua_createtable(L, 0 /* narr */, 6 /* nrec */);

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receive);
    lua_setfield(L, -2, "receive");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receiveuntil);
    lua_setfield(L, -2, "receiveuntil");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_send);
    lua_setfield(L, -2, "send");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_settimeout);
    lua_setfield(L, -2, "settimeout"); /* ngx socket mt */

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_settimeouts);
    lua_setfield(L, -2, "settimeouts"); /* ngx socket mt */

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");

    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* {{{tcp object metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          tcp_socket_metatable_key));
    lua_createtable(L, 0 /* narr */, 12 /* nrec */);

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_connect);
    lua_setfield(L, -2, "connect");

#if (NGX_HTTP_SSL)

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_sslhandshake);
    lua_setfield(L, -2, "sslhandshake");

#endif

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receive);
    lua_setfield(L, -2, "receive");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receiveany);
    lua_setfield(L, -2, "receiveany");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_receiveuntil);
    lua_setfield(L, -2, "receiveuntil");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_send);
    lua_setfield(L, -2, "send");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_close);
    lua_setfield(L, -2, "close");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_setoption);
    lua_setfield(L, -2, "setoption");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_settimeout);
    lua_setfield(L, -2, "settimeout"); /* ngx socket mt */

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_settimeouts);
    lua_setfield(L, -2, "settimeouts"); /* ngx socket mt */

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_getreusedtimes);
    lua_setfield(L, -2, "getreusedtimes");

    lua_pushcfunction(L, ngx_http_lua_socket_tcp_setkeepalive);
    lua_setfield(L, -2, "setkeepalive");

    lua_pushvalue(L, -1);
    lua_setfield(L, -2, "__index");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* {{{upstream userdata metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          upstream_udata_metatable_key));
    lua_createtable(L, 0 /* narr */, 1 /* nrec */); /* metatable */
    lua_pushcfunction(L, ngx_http_lua_socket_tcp_upstream_destroy);
    lua_setfield(L, -2, "__gc");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* {{{downstream userdata metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          downstream_udata_metatable_key));
    lua_createtable(L, 0 /* narr */, 1 /* nrec */); /* metatable */
    lua_pushcfunction(L, ngx_http_lua_socket_downstream_destroy);
    lua_setfield(L, -2, "__gc");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* {{{socket pool userdata metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          pool_udata_metatable_key));
    lua_createtable(L, 0, 1); /* metatable */
    lua_pushcfunction(L, ngx_http_lua_socket_shutdown_pool);
    lua_setfield(L, -2, "__gc");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

    /* {{{socket compiled pattern userdata metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          pattern_udata_metatable_key));
    lua_createtable(L, 0 /* narr */, 1 /* nrec */); /* metatable */
    lua_pushcfunction(L, ngx_http_lua_socket_cleanup_compiled_pattern);
    lua_setfield(L, -2, "__gc");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

#if (NGX_HTTP_SSL)

    /* {{{ssl session userdata metatable */
    lua_pushlightuserdata(L, ngx_http_lua_lightudata_mask(
                          ssl_session_metatable_key));
    lua_createtable(L, 0 /* narr */, 1 /* nrec */); /* metatable */
    lua_pushcfunction(L, ngx_http_lua_ssl_free_session);
    lua_setfield(L, -2, "__gc");
    lua_rawset(L, LUA_REGISTRYINDEX);
    /* }}} */

#endif
}