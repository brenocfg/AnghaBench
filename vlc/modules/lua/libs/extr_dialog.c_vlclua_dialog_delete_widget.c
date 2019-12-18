#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {scalar_t__ type; int b_kill; int /*<<< orphan*/ * p_sys_intf; } ;
typedef  TYPE_1__ extension_widget_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; int /*<<< orphan*/  cond; int /*<<< orphan*/ * p_sys_intf; int /*<<< orphan*/  b_kill; } ;
typedef  TYPE_2__ extension_dialog_t ;

/* Variables and functions */
 int DeleteWidget (TYPE_2__*,TYPE_1__*) ; 
 scalar_t__ EXTENSION_WIDGET_BUTTON ; 
 int /*<<< orphan*/  LUA_REGISTRYINDEX ; 
 int VLC_SUCCESS ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_isuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushlightuserdata (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_settable (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_cond_wait (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int vlc_ext_dialog_update (int /*<<< orphan*/ *,TYPE_2__*) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_dialog_delete_widget( lua_State *L )
{
    /* Get dialog */
    extension_dialog_t **pp_dlg =
            (extension_dialog_t**) luaL_checkudata( L, 1, "dialog" );
    if( !pp_dlg || !*pp_dlg )
        return luaL_error( L, "Can't get pointer to dialog" );
    extension_dialog_t *p_dlg = *pp_dlg;

    /* Get widget */
    if( !lua_isuserdata( L, 2 ) )
        return luaL_error( L, "Argument to del_widget is not a widget" );

    /* Get dialog */
    extension_widget_t **pp_widget =
            (extension_widget_t **) luaL_checkudata( L, 2, "widget" );
    if( !pp_widget || !*pp_widget )
        return luaL_error( L, "Can't get pointer to widget" );
    extension_widget_t *p_widget = *pp_widget;

    /* Delete widget */
    *pp_widget = NULL;
    if( p_widget->type == EXTENSION_WIDGET_BUTTON )
    {
        /* Remove button action from registry */
        lua_pushlightuserdata( L, p_widget );
        lua_pushnil( L );
        lua_settable( L, LUA_REGISTRYINDEX );
    }

    vlc_object_t *p_mgr = vlclua_get_this( L );

    p_widget->b_kill = true;

    lua_SetDialogUpdate( L, 0 ); // Reset update flag
    int i_ret = vlc_ext_dialog_update( p_mgr, p_dlg );

    if( i_ret != VLC_SUCCESS )
    {
        return luaL_error( L, "Could not delete widget" );
    }

    vlc_mutex_lock( &p_dlg->lock );

    /* Same remarks as for dialog delete.
     * If the dialog is deleted or about to be deleted, then there is no
     * need to wait on this particular widget that already doesn't exist
     * anymore in the UI */
    while( p_widget->p_sys_intf != NULL && !p_dlg->b_kill
           && p_dlg->p_sys_intf != NULL )
    {
        vlc_cond_wait( &p_dlg->cond, &p_dlg->lock );
    }

    i_ret = DeleteWidget( p_dlg, p_widget );

    vlc_mutex_unlock( &p_dlg->lock );

    if( i_ret != VLC_SUCCESS )
    {
        return luaL_error( L, "Could not remove widget from list" );
    }

    return 1;
}