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
struct tls_context {int is_close; int /*<<< orphan*/ * out_bio; int /*<<< orphan*/ * in_bio; int /*<<< orphan*/ * ssl; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SSL_free (int /*<<< orphan*/ *) ; 
 struct tls_context* lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int
_ltls_context_close(lua_State* L) {
    struct tls_context* tls_p = lua_touserdata(L, 1);
    if(!tls_p->is_close) {
        SSL_free(tls_p->ssl);
        tls_p->ssl = NULL;
        tls_p->in_bio = NULL; //in_bio and out_bio will be free when SSL_free is called
        tls_p->out_bio = NULL;
        tls_p->is_close = true;
    }
    return 0;
}