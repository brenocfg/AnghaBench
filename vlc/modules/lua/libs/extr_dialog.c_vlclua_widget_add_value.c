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
struct extension_widget_value_t {int b_selected; struct extension_widget_value_t* p_next; int /*<<< orphan*/  i_id; int /*<<< orphan*/  psz_text; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ type; int b_update; TYPE_1__* p_dialog; struct extension_widget_value_t* p_values; } ;
typedef  TYPE_2__ extension_widget_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ EXTENSION_WIDGET_DROPDOWN ; 
 scalar_t__ EXTENSION_WIDGET_LIST ; 
 struct extension_widget_value_t* calloc (int,int) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_tointeger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_widget_add_value( lua_State *L )
{
    /* Get widget */
    extension_widget_t **pp_widget =
            (extension_widget_t **) luaL_checkudata( L, 1, "widget" );
    if( !pp_widget || !*pp_widget )
        return luaL_error( L, "Can't get pointer to widget" );
    extension_widget_t *p_widget = *pp_widget;

    if( p_widget->type != EXTENSION_WIDGET_DROPDOWN
        && p_widget->type != EXTENSION_WIDGET_LIST )
        return luaL_error( L, "method add_value not valid for this widget" );

    if( !lua_isstring( L, 2 ) )
        return luaL_error( L, "widget:add_value usage: (text, id = 0)" );

    struct extension_widget_value_t *p_value,
        *p_new_value = calloc( 1, sizeof( struct extension_widget_value_t ) );
    p_new_value->psz_text = strdup( luaL_checkstring( L, 2 ) );
    p_new_value->i_id = lua_tointeger( L, 3 );

    vlc_mutex_lock( &p_widget->p_dialog->lock );

    if( !p_widget->p_values )
    {
        p_widget->p_values = p_new_value;
        if( p_widget->type == EXTENSION_WIDGET_DROPDOWN )
            p_new_value->b_selected = true;
    }
    else
    {
        for( p_value = p_widget->p_values;
             p_value->p_next != NULL;
             p_value = p_value->p_next )
        { /* Do nothing, iterate to find the end */ }
        p_value->p_next = p_new_value;
    }

    p_widget->b_update = true;
    vlc_mutex_unlock( &p_widget->p_dialog->lock );

    lua_SetDialogUpdate( L, 1 );

    return 1;
}