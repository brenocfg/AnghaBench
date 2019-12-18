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
typedef  int /*<<< orphan*/  extension_dialog_t ;

/* Variables and functions */
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_ext_dialog_update (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_dialog_update( lua_State *L )
{
    vlc_object_t *p_mgr = vlclua_get_this( L );

    extension_dialog_t **pp_dlg =
            (extension_dialog_t**) luaL_checkudata( L, 1, "dialog" );
    if( !pp_dlg || !*pp_dlg )
        return luaL_error( L, "Can't get pointer to dialog" );
    extension_dialog_t *p_dlg = *pp_dlg;

    // Updating dialog immediately
    vlc_ext_dialog_update( p_mgr, p_dlg );

    // Reset update flag
    lua_SetDialogUpdate( L, 0 );

    return 1;
}