#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ type; int b_checked; int b_update; TYPE_1__* p_dialog; } ;
typedef  TYPE_2__ extension_widget_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ EXTENSION_WIDGET_CHECK_BOX ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isboolean (int /*<<< orphan*/ *,int) ; 
 int lua_toboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_widget_set_checked( lua_State *L )
{
    /* Get dialog */
    extension_widget_t **pp_widget =
            (extension_widget_t **) luaL_checkudata( L, 1, "widget" );
    if( !pp_widget || !*pp_widget )
        return luaL_error( L, "Can't get pointer to widget" );
    extension_widget_t *p_widget = *pp_widget;

    if( p_widget->type != EXTENSION_WIDGET_CHECK_BOX )
        return luaL_error( L, "method set_checked not valid for this widget" );

    /* Verify arguments */
    if( !lua_isboolean( L, 2 ) )
        return luaL_error( L, "widget:set_checked usage: (bool)" );

    vlc_mutex_lock( &p_widget->p_dialog->lock );

    bool b_old_check = p_widget->b_checked;
    p_widget->b_checked = lua_toboolean( L, 2 );

    vlc_mutex_unlock( &p_widget->p_dialog->lock );

    if( b_old_check != p_widget->b_checked )
    {
        /* Signal interface of the change */
        p_widget->b_update = true;
        lua_SetDialogUpdate( L, 1 );
    }

    return 1;
}