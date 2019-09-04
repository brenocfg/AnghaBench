#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct tls_context {int is_close; } ;
struct ssl_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 struct ssl_ctx* _check_sslctx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  _init_client_context (int /*<<< orphan*/ *,struct tls_context*,struct ssl_ctx*) ; 
 int /*<<< orphan*/  _init_server_context (int /*<<< orphan*/ *,struct tls_context*,struct ssl_ctx*) ; 
 int /*<<< orphan*/ * _ltls_context_close ; 
 int /*<<< orphan*/ * _ltls_context_finished ; 
 int /*<<< orphan*/ * _ltls_context_handshake ; 
 int /*<<< orphan*/ * _ltls_context_read ; 
 int /*<<< orphan*/ * _ltls_context_write ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setuservalue (int /*<<< orphan*/ *,int) ; 
 scalar_t__ strcmp (char const*,char*) ; 

__attribute__((used)) static int
lnew_tls(lua_State* L) {
    struct tls_context* tls_p = (struct tls_context*)lua_newuserdata(L, sizeof(*tls_p));
    tls_p->is_close = false;
    const char* method = luaL_optstring(L, 1, "nil");
    struct ssl_ctx* ctx_p = _check_sslctx(L, 2);
    lua_pushvalue(L, 2);
    lua_setuservalue(L, -2); // set ssl_ctx associated to tls_context

    if(strcmp(method, "client") == 0) {
        _init_client_context(L, tls_p, ctx_p);
    }else if(strcmp(method, "server") == 0) {
        _init_server_context(L, tls_p, ctx_p);
    } else {
        luaL_error(L, "invalid method:%s e.g[server, client]", method);
    }

    if(luaL_newmetatable(L, "_TLS_CONTEXT_METATABLE_")) {
        luaL_Reg l[] = {
            {"close", _ltls_context_close},
            {"finished", _ltls_context_finished},
            {"handshake", _ltls_context_handshake},
            {"read", _ltls_context_read},
            {"write", _ltls_context_write},
            {NULL, NULL},
        };
        luaL_newlib(L, l);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, _ltls_context_close);
        lua_setfield(L, -2, "__gc");
    }
    lua_setmetatable(L, -2);
    return 1;
}