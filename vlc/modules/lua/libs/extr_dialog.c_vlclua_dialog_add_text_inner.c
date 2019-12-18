#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_4__ {int type; int /*<<< orphan*/  psz_text; } ;
typedef  TYPE_1__ extension_widget_t ;

/* Variables and functions */
 TYPE_1__* calloc (int,int) ; 
 int /*<<< orphan*/  luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_isnil (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_isstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strdup (int /*<<< orphan*/ ) ; 
 int vlclua_create_widget_inner (int /*<<< orphan*/ *,int,TYPE_1__*) ; 

__attribute__((used)) static int vlclua_dialog_add_text_inner( lua_State *L, int i_type )
{
    /* Verify arguments */
    if( !lua_isstring( L, 2 ) && !lua_isnil( L, 2 ) )
        return luaL_error( L, "dialog:add_text_input usage: (text = nil)" );

    extension_widget_t *p_widget = calloc( 1, sizeof( extension_widget_t ) );
    p_widget->type = i_type;
    if( !lua_isnil( L, 2 ) )
        p_widget->psz_text = strdup( luaL_checkstring( L, 2 ) );

    return vlclua_create_widget_inner( L, 1, p_widget );
}