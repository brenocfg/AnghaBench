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
struct tls_context {scalar_t__ is_close; } ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_touserdata (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static struct tls_context *
_check_context(lua_State* L, int idx) {
    struct tls_context* tls_p = (struct tls_context*)lua_touserdata(L, idx);
    if(!tls_p) {
        luaL_error(L, "need tls context");
    }
    if(tls_p->is_close) {
        luaL_error(L, "context is closed");
    }
    return tls_p;
}