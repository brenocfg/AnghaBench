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
struct TYPE_4__ {int type; int b_update; TYPE_1__* p_dialog; int /*<<< orphan*/  psz_text; } ;
typedef  TYPE_2__ extension_widget_t ;
struct TYPE_3__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
#define  EXTENSION_WIDGET_BUTTON 136 
#define  EXTENSION_WIDGET_CHECK_BOX 135 
#define  EXTENSION_WIDGET_DROPDOWN 134 
#define  EXTENSION_WIDGET_HTML 133 
#define  EXTENSION_WIDGET_IMAGE 132 
#define  EXTENSION_WIDGET_LABEL 131 
#define  EXTENSION_WIDGET_LIST 130 
#define  EXTENSION_WIDGET_PASSWORD 129 
#define  EXTENSION_WIDGET_TEXT_FIELD 128 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_SetDialogUpdate (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_widget_set_text( lua_State *L )
{
    /* Get dialog */
    extension_widget_t **pp_widget =
            (extension_widget_t **) luaL_checkudata( L, 1, "widget" );
    if( !pp_widget || !*pp_widget )
        return luaL_error( L, "Can't get pointer to widget" );
    extension_widget_t *p_widget = *pp_widget;

    /* Verify arguments */
    if( !lua_isstring( L, 2 ) )
        return luaL_error( L, "widget:set_text usage: (text)" );

    /* Verify widget type */
    switch( p_widget->type )
    {
        case EXTENSION_WIDGET_LABEL:
        case EXTENSION_WIDGET_BUTTON:
        case EXTENSION_WIDGET_HTML:
        case EXTENSION_WIDGET_TEXT_FIELD:
        case EXTENSION_WIDGET_PASSWORD:
        case EXTENSION_WIDGET_DROPDOWN:
        case EXTENSION_WIDGET_CHECK_BOX:
            break;
        case EXTENSION_WIDGET_LIST:
        case EXTENSION_WIDGET_IMAGE:
        default:
            return luaL_error( L, "method set_text not valid for this widget" );
    }

    vlc_mutex_lock( &p_widget->p_dialog->lock );

    /* Update widget */
    p_widget->b_update = true;
    free( p_widget->psz_text );
    p_widget->psz_text = strdup( luaL_checkstring( L, 2 ) );

    vlc_mutex_unlock( &p_widget->p_dialog->lock );

    lua_SetDialogUpdate( L, 1 );

    return 1;
}