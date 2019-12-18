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
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
#define  VLC_VAR_BOOL 131 
#define  VLC_VAR_FLOAT 130 
#define  VLC_VAR_INTEGER 129 
#define  VLC_VAR_STRING 128 
 int /*<<< orphan*/  config_GetFloat (char const*) ; 
 int /*<<< orphan*/  config_GetInt (char const*) ; 
 char* config_GetPsz (char const*) ; 
 int config_GetType (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_pushboolean (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushinteger (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushnumber (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_config_get( lua_State *L )
{
    const char *psz_name = luaL_checkstring( L, 1 );
    switch( config_GetType( psz_name ) )
    {
        case VLC_VAR_STRING:
        {
            char *psz = config_GetPsz( psz_name );
            lua_pushstring( L, psz );
            free( psz );
            break;
        }

        case VLC_VAR_INTEGER:
            lua_pushinteger( L, config_GetInt( psz_name ) );
            break;

        case VLC_VAR_BOOL:
            lua_pushboolean( L, config_GetInt( psz_name ) );
            break;

        case VLC_VAR_FLOAT:
            lua_pushnumber( L, config_GetFloat( psz_name ) );
            break;

        default:
            return vlclua_error( L );

    }
    return 1;
}