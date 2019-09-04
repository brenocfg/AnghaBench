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
struct ssl_ctx {int dummy; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct ssl_ctx *
_check_sslctx(lua_State* L, int idx) {
    struct ssl_ctx* ctx_p = (struct ssl_ctx*)lua_touserdata(L, idx);
    if(!ctx_p) {
        luaL_error(L, "need sslctx");
    }
    return ctx_p;
}