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
typedef  int /*<<< orphan*/  vlc_object_t ;
typedef  int /*<<< orphan*/  lua_State ;
struct TYPE_3__ {int /*<<< orphan*/  psz_name; } ;
typedef  TYPE_1__ extension_t ;

/* Variables and functions */
 int asprintf (char**,char*,char*,char const*) ; 
 int /*<<< orphan*/  free (char*) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,...) ; 
 int /*<<< orphan*/  msg_Dbg (int /*<<< orphan*/ *,char*,char const*) ; 
 char* strdup (int /*<<< orphan*/ ) ; 
 int strlen (char*) ; 
 char* strrchr (char*,char) ; 
 int vlclua_dofile (int /*<<< orphan*/ *,int /*<<< orphan*/ *,char*) ; 
 TYPE_1__* vlclua_extension_get (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_this (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_extension_require( lua_State *L )
{
    const char *psz_module = luaL_checkstring( L, 1 );
    vlc_object_t *p_this = vlclua_get_this( L );
    extension_t *p_ext = vlclua_extension_get( L );
    msg_Dbg( p_this, "loading module '%s' from extension package",
             psz_module );
    char *psz_fullpath, *psz_package, *sep;
    psz_package = strdup( p_ext->psz_name );
    sep = strrchr( psz_package, '/' );
    if( !sep )
    {
        free( psz_package );
        return luaL_error( L, "could not find package name" );
    }
    *sep = '\0';
    if( -1 == asprintf( &psz_fullpath,
                        "%s/modules/%s.luac", psz_package, psz_module ) )
    {
        free( psz_package );
        return 1;
    }
    int i_ret = vlclua_dofile( p_this, L, psz_fullpath );
    if( i_ret != 0 )
    {
        // Remove trailing 'c' --> try with .lua script
        psz_fullpath[ strlen( psz_fullpath ) - 1 ] = '\0';
        i_ret = vlclua_dofile( p_this, L, psz_fullpath );
    }
    free( psz_fullpath );
    free( psz_package );
    if( i_ret != 0 )
    {
        return luaL_error( L, "unable to load module '%s' from package",
                           psz_module );
    }
    return 0;
}