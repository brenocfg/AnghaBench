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

/* Variables and functions */
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int lua_gettop (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 
 int var_GetBool (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  var_SetBool (int /*<<< orphan*/ *,char const*,int) ; 
 int var_ToggleBool (int /*<<< orphan*/ *,char const*) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 

int vlclua_var_toggle_or_set( lua_State *L, vlc_object_t *p_obj,
                              const char *psz_name )
{
    bool b_bool;
    if( lua_gettop( L ) > 1 ) return vlclua_error( L );

    if( lua_gettop( L ) == 0 )
    {
        b_bool = var_ToggleBool( p_obj, psz_name );
        goto end;
    }

    /* lua_gettop( L ) == 1 */
    const char *s = luaL_checkstring( L, -1 );
    lua_pop( L, 1 );

    if( s && !strcmp(s, "on") )
        b_bool = true;
    else if( s && !strcmp(s, "off") )
        b_bool = false;
    else
    {
        b_bool = var_GetBool( p_obj, psz_name );
        goto end;
    }

    if( b_bool != var_GetBool( p_obj, psz_name ) )
        var_SetBool( p_obj, psz_name, b_bool );

end:
    lua_pushboolean( L, b_bool );
    return 1;
}