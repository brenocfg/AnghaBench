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
 int config_GetType (char const*) ; 
 int /*<<< orphan*/  config_PutFloat (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_PutInt (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  config_PutPsz (char const*,char*) ; 
 int /*<<< orphan*/  luaL_checkboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int vlclua_error (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_config_set( lua_State *L )
{
    const char *psz_name = luaL_checkstring( L, 1 );
    switch( config_GetType( psz_name ) )
    {
        case VLC_VAR_STRING:
            config_PutPsz( psz_name, luaL_checkstring( L, 2 ) );
            break;

        case VLC_VAR_INTEGER:
            config_PutInt( psz_name, luaL_checkinteger( L, 2 ) );
            break;

        case VLC_VAR_BOOL:
            config_PutInt( psz_name, luaL_checkboolean( L, 2 ) );
            break;

        case VLC_VAR_FLOAT:
            config_PutFloat( psz_name, luaL_checknumber( L, 2 ) );
            break;

        default:
            return vlclua_error( L );
    }
    return 0;
}