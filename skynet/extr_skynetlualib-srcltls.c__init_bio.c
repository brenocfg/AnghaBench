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
struct tls_context {void* out_bio; void* in_bio; int /*<<< orphan*/  ssl; } ;
struct ssl_ctx {int /*<<< orphan*/  ctx; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 void* BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_mem () ; 
 int /*<<< orphan*/  BIO_set_mem_eof_return (void*,int) ; 
 int /*<<< orphan*/  SSL_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_set_bio (int /*<<< orphan*/ ,void*,void*) ; 
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static void
_init_bio(lua_State* L, struct tls_context* tls_p, struct ssl_ctx* ctx_p) {
    tls_p->ssl = SSL_new(ctx_p->ctx);
    if(!tls_p->ssl) {
        luaL_error(L, "SSL_new faild");
    }

    tls_p->in_bio = BIO_new(BIO_s_mem());
    if(!tls_p->in_bio) {
        luaL_error(L, "new in bio faild");
    }
    BIO_set_mem_eof_return(tls_p->in_bio, -1); /* see: https://www.openssl.org/docs/crypto/BIO_s_mem.html */

    tls_p->out_bio = BIO_new(BIO_s_mem());
    if(!tls_p->out_bio) {
        luaL_error(L, "new out bio faild");
    }
    BIO_set_mem_eof_return(tls_p->out_bio, -1); /* see: https://www.openssl.org/docs/crypto/BIO_s_mem.html */

    SSL_set_bio(tls_p->ssl, tls_p->in_bio, tls_p->out_bio);
}