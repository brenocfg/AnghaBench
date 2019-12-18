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
struct extension_widget_value_t {struct extension_widget_value_t* psz_text; struct extension_widget_value_t* p_next; } ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {scalar_t__ type; int b_update; TYPE_1__* p_dialog; struct extension_widget_value_t* p_values; } ;
typedef  TYPE_2__ extension_widget_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 scalar_t__ EXTENSION_WIDGET_DROPDOWN ; 
 scalar_t__ EXTENSION_WIDGET_LIST ; 
 int /*<<< orphan*/  free (struct extension_widget_value_t*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_widget_clear( lua_State *L )
{
    /* Get widget */
    extension_widget_t **pp_widget =
            (extension_widget_t **) luaL_checkudata( L, 1, "widget" );
    if( !pp_widget || !*pp_widget )
        return luaL_error( L, "Can't get pointer to widget" );
    extension_widget_t *p_widget = *pp_widget;

    if( p_widget->type != EXTENSION_WIDGET_DROPDOWN
        && p_widget->type != EXTENSION_WIDGET_LIST )
        return luaL_error( L, "method clear not valid for this widget" );

    struct extension_widget_value_t *p_value, *p_next;

    vlc_mutex_lock( &p_widget->p_dialog->lock );

    for( p_value = p_widget->p_values;
         p_value != NULL;
         p_value = p_next )
    {
        p_next = p_value->p_next;
        free( p_value->psz_text );
        free( p_value );
    }

    p_widget->p_values = NULL;
    p_widget->b_update = true;

    vlc_mutex_unlock( &p_widget->p_dialog->lock );

    lua_SetDialogUpdate( L, 1 );

    return 1;
}