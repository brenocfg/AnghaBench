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
typedef  int /*<<< orphan*/  vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  LUA_TBOOLEAN 131 
#define  LUA_TNIL 130 
#define  LUA_TNUMBER 129 
#define  LUA_TSTRING 128 
 int VLC_SUCCESS ; 
 int VLC_VAR_BOOL ; 
 int VLC_VAR_FLOAT ; 
 int VLC_VAR_STRING ; 
 int VLC_VAR_VOID ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ ** luaL_checkudata (int /*<<< orphan*/ *,int,char*) ; 
 int lua_type (int /*<<< orphan*/ *,int) ; 
 int var_Create (int /*<<< orphan*/ *,char const*,int) ; 
 int var_Set (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 
 int vlclua_push_ret (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  vlclua_tovalue (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_var_create( lua_State *L )
{
    int i_type, i_ret;
    vlc_object_t **pp_obj = luaL_checkudata( L, 1, "vlc_object" );
    const char *psz_var = luaL_checkstring( L, 2 );

    switch( lua_type( L, 3 ) )
    {
        case LUA_TNUMBER:
            i_type = VLC_VAR_FLOAT;
            break;
        case LUA_TBOOLEAN:
            i_type = VLC_VAR_BOOL;
            break;
        case LUA_TSTRING:
            i_type = VLC_VAR_STRING;
            break;
        case LUA_TNIL:
            i_type = VLC_VAR_VOID;
            break;
        default:
            return 0;
    }

    if( ( i_ret = var_Create( *pp_obj, psz_var, i_type ) ) != VLC_SUCCESS )
        return vlclua_push_ret( L, i_ret );

    // Special case for void variables
    if( i_type == VLC_VAR_VOID )
        return 0;

    vlc_value_t val;
    vlclua_tovalue( L, i_type, &val );
    return vlclua_push_ret( L, var_Set( *pp_obj, psz_var, val ) );
}