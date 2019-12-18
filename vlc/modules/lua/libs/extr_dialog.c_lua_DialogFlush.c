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
typedef  int /*<<< orphan*/  extension_dialog_t ;

/* Variables and functions */
 int VLC_SUCCESS ; 
 scalar_t__ lua_GetDialogUpdate (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ lua_topointer (int /*<<< orphan*/ *,int) ; 
 int vlc_ext_dialog_update (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_get_this (int /*<<< orphan*/ *) ; 

int lua_DialogFlush( lua_State *L )
{
    lua_getglobal( L, "vlc" );
    lua_getfield( L, -1, "__dialog" );
    extension_dialog_t *p_dlg = ( extension_dialog_t* )lua_topointer( L, -1 );

    if( !p_dlg )
        return VLC_SUCCESS;

    int i_ret = VLC_SUCCESS;
    if( lua_GetDialogUpdate( L ) )
    {
        i_ret = vlc_ext_dialog_update( vlclua_get_this( L ), p_dlg );
        lua_SetDialogUpdate( L, 0 );
    }

    return i_ret;
}