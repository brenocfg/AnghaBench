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
struct tls_context {int /*<<< orphan*/  ssl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int SSL_is_init_finished (int /*<<< orphan*/ ) ; 
 struct tls_context* _check_context (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_ltls_context_finished(lua_State* L) {
    struct tls_context* tls_p = _check_context(L, 1);
    int b = SSL_is_init_finished(tls_p->ssl);
    lua_pushboolean(L, b);
    return 1;
}