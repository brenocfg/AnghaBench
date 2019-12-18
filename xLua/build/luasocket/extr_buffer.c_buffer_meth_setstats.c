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
typedef  TYPE_1__* p_buffer ;
typedef  int /*<<< orphan*/  lua_State ;
typedef  int /*<<< orphan*/  lua_Number ;
struct TYPE_3__ {long received; long sent; scalar_t__ birthday; } ;

/* Variables and functions */
 scalar_t__ luaL_optnumber (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_tonumber (int /*<<< orphan*/ *,int) ; 
 scalar_t__ timeout_gettime () ; 

int buffer_meth_setstats(lua_State *L, p_buffer buf) {
    buf->received = (long) luaL_optnumber(L, 2, (lua_Number) buf->received); 
    buf->sent = (long) luaL_optnumber(L, 3, (lua_Number) buf->sent); 
    if (lua_isnumber(L, 4)) buf->birthday = timeout_gettime() - lua_tonumber(L, 4);
    lua_pushnumber(L, 1);
    return 1;
}