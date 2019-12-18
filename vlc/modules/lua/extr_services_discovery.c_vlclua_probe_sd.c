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
typedef  int /*<<< orphan*/  vlc_probe_t ;
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  SD_CAT_INTERNET ; 
 int VLC_ENOMEM ; 
 int VLC_PROBE_CONTINUE ; 
 int asprintf (char**,char*,char*) ; 
 char* config_StringEscape (char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/ * luaL_newstate () ; 
 int /*<<< orphan*/  luaL_openlibs (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_close (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_tostring (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  msg_Err (int /*<<< orphan*/ *,char*,...) ; 
 int vlc_sd_probe_Add (int /*<<< orphan*/ *,char*,char const*,int /*<<< orphan*/ ) ; 
 scalar_t__ vlclua_add_modules_path (int /*<<< orphan*/ *,char*) ; 
 scalar_t__ vlclua_dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 char* vlclua_find_file (char*,char const*) ; 
 char* vlclua_sd_description (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 

int vlclua_probe_sd( vlc_object_t *obj, const char *name )
{
    vlc_probe_t *probe = (vlc_probe_t *)obj;

    char *filename = vlclua_find_file( "sd", name );
    if( filename == NULL )
    {
        // File suddenly disappeared - maybe a race condition, no problem
        msg_Err( probe, "Couldn't probe lua services discovery script \"%s\".",
                 name );
        return VLC_PROBE_CONTINUE;
    }

    lua_State *L = luaL_newstate();
    if( !L )
    {
        msg_Err( probe, "Could not create new Lua State" );
        free( filename );
        return VLC_ENOMEM;
    }
    luaL_openlibs( L );
    if( vlclua_add_modules_path( L, filename ) )
    {
        msg_Err( probe, "Error while setting the module search path for %s",
                 filename );
        lua_close( L );
        free( filename );
        return VLC_ENOMEM;
    }
    if( vlclua_dofile( obj, L, filename ) )
    {
        msg_Err( probe, "Error loading script %s: %s", filename,
                 lua_tostring( L, -1 ) );
        lua_close( L );
        free( filename );
        return VLC_PROBE_CONTINUE;
    }
    const char *description = vlclua_sd_description( obj, L, filename );
    if( description == NULL )
        description = name;

    int r = VLC_ENOMEM;
    char *name_esc = config_StringEscape( name );
    char *chain;
    if( asprintf( &chain, "lua{sd='%s'}", name_esc ) != -1 )
    {
        r = vlc_sd_probe_Add( probe, chain, description, SD_CAT_INTERNET );
        free( chain );
    }
    free( name_esc );

    lua_close( L );
    free( filename );
    return r;
}