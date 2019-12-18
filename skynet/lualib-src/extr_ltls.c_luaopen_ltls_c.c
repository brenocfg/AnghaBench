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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {char* member_0; int /*<<< orphan*/ * member_1; } ;
typedef  TYPE_1__ luaL_Reg ;

/* Variables and functions */
 int /*<<< orphan*/ * lnew_ctx ; 
 int /*<<< orphan*/ * lnew_tls ; 
 int /*<<< orphan*/  luaL_checkversion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  luaL_newlib (int /*<<< orphan*/ *,TYPE_1__*) ; 

int
luaopen_ltls_c(lua_State* L) {
    luaL_Reg l[] = {
        {"newctx", lnew_ctx},
        {"newtls", lnew_tls},
        {NULL, NULL},
    };
    luaL_checkversion(L);
    luaL_newlib(L, l);
    return 1;
}