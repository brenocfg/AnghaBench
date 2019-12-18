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
struct TYPE_4__ {int /*<<< orphan*/  psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 scalar_t__ VLC_SUCCESS ; 
 int VLC_VAR_STRING ; 
 int /*<<< orphan*/  free (int /*<<< orphan*/ ) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 scalar_t__ var_Get (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 int var_Type (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlclua_pushvalue (int /*<<< orphan*/ *,int,TYPE_1__) ; 

__attribute__((used)) static int vlclua_var_get( lua_State *L )
{
    vlc_value_t val;
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );

    int i_type = var_Type( *pp_obj, psz_var );
    if( var_Get( *pp_obj, psz_var, &val ) != VLC_SUCCESS )
        return 0;

    lua_pop( L, 2 );
    vlclua_pushvalue( L, i_type, val );
    if( i_type == VLC_VAR_STRING )
        free( val.psz_string );
    return 1;
}