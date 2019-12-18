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
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int /*<<< orphan*/  key_opaque ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushcfunction (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlclua_dialog_create ; 

void luaopen_dialog( lua_State *L, void *opaque )
{
    lua_getglobal( L, "vlc" );
    lua_pushcfunction( L, vlclua_dialog_create );
    lua_setfield( L, -2, "dialog" );

    /* Add a private pointer (opaque) in the registry
     * The &key pointer is used to have a unique entry in the registry
     */
    lua_pushlightuserdata( L, (void*) &key_opaque );
    lua_pushlightuserdata( L, opaque );
    lua_settable( L, LUA_REGISTRYINDEX );

    /* Add private data: dialog update flag */
    lua_SetDialogUpdate( L, 0 );
}