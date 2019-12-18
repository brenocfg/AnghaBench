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
typedef  TYPE_1__* p_tcp ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_2__ {scalar_t__ sock; } ;

/* Variables and functions */
 int /*<<< orphan*/  auxiliar_checkgroup (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int meth_getfd(lua_State *L)
{
    p_tcp tcp = (p_tcp) auxiliar_checkgroup(L, "tcp{any}", 1);
    lua_pushnumber(L, (int) tcp->sock);
    return 1;
}