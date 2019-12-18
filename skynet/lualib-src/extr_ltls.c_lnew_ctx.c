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
struct ssl_ctx {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ luaL_Reg ;
typedef  int /*<<< orphan*/  buf ;

/* Variables and functions */
 int /*<<< orphan*/  ERR_error_string_n (unsigned int,char*,int) ; 
 unsigned int ERR_get_error () ; 
 int /*<<< orphan*/  SSL_CTX_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSLv23_method () ; 
 int /*<<< orphan*/ * _lctx_cert ; 
 int /*<<< orphan*/ * _lctx_ciphers ; 
 int /*<<< orphan*/  _lctx_gc ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,char*) ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,TYPE_1__*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
lnew_ctx(lua_State* L) {
    struct ssl_ctx* ctx_p = (struct ssl_ctx*)lua_newuserdata(L, sizeof(*ctx_p));
    ctx_p->ctx = SSL_CTX_new(SSLv23_method());
    if(!ctx_p->ctx) {
        unsigned int err = ERR_get_error();
        char buf[256];
        ERR_error_string_n(err, buf, sizeof(buf));
        luaL_error(L, "SSL_CTX_new client faild. %s\n", buf);
    }

    if(luaL_newmetatable(L, "_TLS_SSLCTX_METATABLE_")) {
        luaL_Reg l[] = {
            {"set_ciphers", _lctx_ciphers},
            {"set_cert", _lctx_cert},
            {NULL, NULL},
        };

        luaL_newlib(L, l);
        lua_setfield(L, -2, "__index");
        lua_pushcfunction(L, _lctx_gc);
        lua_setfield(L, -2, "__gc");
    }
    lua_setmetatable(L, -2);
    return 1;
}