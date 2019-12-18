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
struct TYPE_3__ {int type; scalar_t__ psz_text; TYPE_2__* p_dialog; } ;
typedef  TYPE_1__ extension_widget_t ;
struct TYPE_4__ {int /*<<< orphan*/  lock; } ;
typedef  TYPE_2__ extension_dialog_t ;

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
 int /*<<< orphan*/  free (char*) ; 
 scalar_t__ luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 char* strdup (scalar_t__) ; 
 int /*<<< orphan*/  vlc_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlc_mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_widget_get_text( lua_State *L )
{
    /* Get dialog */
    extension_widget_t **pp_widget =
            (extension_widget_t **) luaL_checkudata( L, 1, "widget" );
    if( !pp_widget || !*pp_widget )
        return luaL_error( L, "Can't get pointer to widget" );
    extension_widget_t *p_widget = *pp_widget;

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
            return luaL_error( L, "method get_text not valid for this widget" );
    }

    extension_dialog_t *p_dlg = p_widget->p_dialog;
    vlc_mutex_lock( &p_dlg->lock );

    char *psz_text = NULL;
    if( p_widget->psz_text )
        psz_text = strdup( p_widget->psz_text );
    vlc_mutex_unlock( &p_dlg->lock );

    lua_pushstring( L, psz_text );

    free( psz_text );
    return 1;
}