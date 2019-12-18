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
 int SSL_CTX_check_private_key (int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_PrivateKey_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int SSL_CTX_use_certificate_file (int /*<<< orphan*/ ,char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_FILETYPE_PEM ; 
 struct ssl_ctx* _check_sslctx (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 char* lua_tostring (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_lctx_cert(lua_State* L) {
    struct ssl_ctx* ctx_p = _check_sslctx(L, 1);
    const char* certfile = lua_tostring(L, 2);
    const char* key = lua_tostring(L, 3);
    if(!certfile) {
        luaL_error(L, "need certfile");
    }

    if(!key) {
        luaL_error(L, "need private key");
    }

    int ret = SSL_CTX_use_certificate_file(ctx_p->ctx, certfile, SSL_FILETYPE_PEM);
    if(ret != 1) {
        luaL_error(L, "SSL_CTX_use_certificate_file error:%d", ret);
    }

    ret = SSL_CTX_use_PrivateKey_file(ctx_p->ctx, key, SSL_FILETYPE_PEM);
    if(ret != 1) {
        luaL_error(L, "SSL_CTX_use_PrivateKey_file error:%d", ret);
    }
    ret = SSL_CTX_check_private_key(ctx_p->ctx);
    if(ret != 1) {
        luaL_error(L, "SSL_CTX_check_private_key error:%d", ret);
    }
    return 0;
}