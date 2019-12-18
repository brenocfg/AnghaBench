#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {char* psz_string; } ;
typedef  TYPE_1__ vlc_value_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/ * VLC_OBJECT (int /*<<< orphan*/ ) ; 
 int VLC_VAR_ISCOMMAND ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int var_Set (int /*<<< orphan*/ *,char const*,TYPE_1__) ; 
 int var_Type (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/  vlc_object_instance (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 
 int vlclua_push_ret (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_libvlc_command( lua_State *L )
{
    vlc_object_t * p_this = vlclua_get_this( L );
    vlc_object_t *vlc = VLC_OBJECT(vlc_object_instance(p_this));
    vlc_value_t val_arg;

    const char *psz_cmd = luaL_checkstring( L, 1 );
    val_arg.psz_string = (char*)luaL_optstring( L, 2, "" );

    int i_type = var_Type( vlc, psz_cmd );
    if( ! (i_type & VLC_VAR_ISCOMMAND) )
    {
        return luaL_error( L, "libvlc's \"%s\" is not a command",
                           psz_cmd );
    }

    int i_ret = var_Set( vlc, psz_cmd, val_arg );
    lua_pop( L, 2 );

    return vlclua_push_ret( L, i_ret );
}