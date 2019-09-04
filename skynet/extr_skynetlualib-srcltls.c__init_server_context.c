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
struct tls_context {int is_server; int /*<<< orphan*/  ssl; } ;
struct ssl_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_set_accept_state (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  _init_bio (int /*<<< orphan*/ *,struct tls_context*,struct ssl_ctx*) ; 

__attribute__((used)) static void
_init_server_context(lua_State* L, struct tls_context* tls_p, struct ssl_ctx* ctx_p) {
    tls_p->is_server = true;
    _init_bio(L, tls_p, ctx_p);
    SSL_set_accept_state(tls_p->ssl);
}