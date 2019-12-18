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
struct ssl_ctx {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int SSL_CTX_set_tlsext_use_srtp (int /*<<< orphan*/ ,char const*) ; 
 struct ssl_ctx* _check_sslctx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_lctx_ciphers(lua_State* L) {
    struct ssl_ctx* ctx_p = _check_sslctx(L, 1);
    const char* s = lua_tostring(L, 2);
    if(!s) {
        luaL_error(L, "need cipher list");
    }
    int ret = SSL_CTX_set_tlsext_use_srtp(ctx_p->ctx, s);
    if(ret != 0) {
        luaL_error(L, "SSL_CTX_set_tlsext_use_srtp error:%d", ret);
    }
    return 0;
}