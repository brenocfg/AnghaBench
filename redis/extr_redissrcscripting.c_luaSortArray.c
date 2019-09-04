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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  lua_call (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_gettable (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_pcall (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushvalue (int /*<<< orphan*/ *,int) ; 

void luaSortArray(lua_State *lua) {
    /* Initial Stack: array */
    lua_getglobal(lua,"table");
    lua_pushstring(lua,"sort");
    lua_gettable(lua,-2);       /* Stack: array, table, table.sort */
    lua_pushvalue(lua,-3);      /* Stack: array, table, table.sort, array */
    if (lua_pcall(lua,1,0,0)) {
        /* Stack: array, table, error */

        /* We are not interested in the error, we assume that the problem is
         * that there are 'false' elements inside the array, so we try
         * again with a slower function but able to handle this case, that
         * is: table.sort(table, __redis__compare_helper) */
        lua_pop(lua,1);             /* Stack: array, table */
        lua_pushstring(lua,"sort"); /* Stack: array, table, sort */
        lua_gettable(lua,-2);       /* Stack: array, table, table.sort */
        lua_pushvalue(lua,-3);      /* Stack: array, table, table.sort, array */
        lua_getglobal(lua,"__redis__compare_helper");
        /* Stack: array, table, table.sort, array, __redis__compare_helper */
        lua_call(lua,2,0);
    }
    /* Stack: array (sorted), table */
    lua_pop(lua,1);             /* Stack: array (sorted) */
}