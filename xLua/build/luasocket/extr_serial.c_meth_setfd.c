#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ t_socket ;
typedef  TYPE_1__* p_unix ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxiliar_checkgroup (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ luaL_checknumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int meth_setfd(lua_State *L) {
    p_unix un = (p_unix) auxiliar_checkgroup(L, "serial{any}", 1);
    un->sock = (t_socket) luaL_checknumber(L, 2); 
    return 0;
}