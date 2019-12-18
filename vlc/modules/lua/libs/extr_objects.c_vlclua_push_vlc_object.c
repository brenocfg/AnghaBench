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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int (*) (int /*<<< orphan*/ *)) ; 
 int /*<<< orphan*/  lua_pushliteral (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_push_vlc_object(lua_State *L, vlc_object_t *p_obj,
                                  int (*release)(lua_State *))
{
    vlc_object_t **udata =
        (vlc_object_t **)lua_newuserdata(L, sizeof (vlc_object_t *));

    *udata = p_obj;

    if (luaL_newmetatable(L, "vlc_object"))
    {
        /* Hide the metatable */
        lua_pushliteral(L, "none of your business");
        lua_setfield(L, -2, "__metatable");
        /* Set the garbage collector if needed */
        if (release != NULL)
        {
            lua_pushcfunction(L, release);
            lua_setfield(L, -2, "__gc");
        }
    }
    lua_setmetatable(L, -2);
    return 1;
}