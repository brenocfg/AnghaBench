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
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_7__ {void* i_height; void* i_width; void* i_vert_span; void* i_horiz_span; void* i_row; void* i_column; TYPE_2__* p_dialog; } ;
typedef  TYPE_1__ extension_widget_t ;
struct TYPE_8__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ extension_dialog_t ;

/* Variables and functions */
 int /*<<< orphan*/  AddWidget (TYPE_2__*,TYPE_1__*) ; 
 void* luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ luaL_newmetatable (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  luaL_register (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int) ; 
 scalar_t__ lua_isnumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 TYPE_1__** lua_newuserdata (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_setmetatable (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_widget_reg ; 

__attribute__((used)) static int vlclua_create_widget_inner( lua_State *L, int i_args,
                                       extension_widget_t *p_widget )
{
    int arg = i_args + 2;

    /* Get dialog */
    extension_dialog_t **pp_dlg =
            (extension_dialog_t**) luaL_checkudata( L, 1, "dialog" );
    if( !pp_dlg || !*pp_dlg )
        return luaL_error( L, "Can't get pointer to dialog" );
    extension_dialog_t *p_dlg = *pp_dlg;

    /* Set parent dialog */
    p_widget->p_dialog = p_dlg;

    /* Set common arguments: col, row, hspan, vspan, width, height */
    if( lua_isnumber( L, arg ) )
        p_widget->i_column = luaL_checkinteger( L, arg );
    else goto end_of_args;
    if( lua_isnumber( L, ++arg ) )
        p_widget->i_row = luaL_checkinteger( L, arg );
    else goto end_of_args;
    if( lua_isnumber( L, ++arg ) )
        p_widget->i_horiz_span = luaL_checkinteger( L, arg );
    else goto end_of_args;
    if( lua_isnumber( L, ++arg ) )
        p_widget->i_vert_span = luaL_checkinteger( L, arg );
    else goto end_of_args;
    if( lua_isnumber( L, ++arg ) )
        p_widget->i_width = luaL_checkinteger( L, arg );
    else goto end_of_args;
    if( lua_isnumber( L, ++arg ) )
        p_widget->i_height = luaL_checkinteger( L, arg );
    else goto end_of_args;

end_of_args:
    vlc_mutex_lock( &p_dlg->lock );

    /* Add the widget to the dialog descriptor */
    AddWidget( p_dlg, p_widget );

    vlc_mutex_unlock( &p_dlg->lock );

    /* Create meta table */
    extension_widget_t **pp_widget = lua_newuserdata( L, sizeof( extension_widget_t* ) );
    *pp_widget = p_widget;
    if( luaL_newmetatable( L, "widget" ) )
    {
        lua_newtable( L );
        luaL_register( L, NULL, vlclua_widget_reg );
        lua_setfield( L, -2, "__index" );
    }
    lua_setmetatable( L, -2 );

    lua_SetDialogUpdate( L, 1 );

    return 1;
}