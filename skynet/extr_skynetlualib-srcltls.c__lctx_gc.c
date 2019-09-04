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
struct ssl_ctx {int /*<<< orphan*/ * ctx; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_CTX_free (int /*<<< orphan*/ *) ; 
 struct ssl_ctx* _check_sslctx (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_lctx_gc(lua_State* L) {
    struct ssl_ctx* ctx_p = _check_sslctx(L, 1);
    if(ctx_p->ctx) {
        SSL_CTX_free(ctx_p->ctx);
        ctx_p->ctx = NULL;
    }
    return 0;
}