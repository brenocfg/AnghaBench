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
 char DIR_SEP_CHAR ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lua_concat (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_getfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  lua_getglobal (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_pop (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ strcmp (char*,char*) ; 
 char* strdup (char const*) ; 
 char* strrchr (char*,char) ; 
 scalar_t__ vlclua_add_modules_path_inner (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  vlclua_dir_list (char*,char***) ; 
 int /*<<< orphan*/  vlclua_dir_list_free (char**) ; 

int vlclua_add_modules_path( lua_State *L, const char *psz_filename )
{
    /* Setup the module search path:
     *   * "The script's directory"/modules
     *   * "The script's parent directory"/modules
     *   * and so on for all the next directories in the directory list
     */
    char *psz_path = strdup( psz_filename );
    if( !psz_path )
        return 1;

    char *psz_char = strrchr( psz_path, DIR_SEP_CHAR );
    if( !psz_char )
    {
        free( psz_path );
        return 1;
    }
    *psz_char = '\0';

    /* psz_path now holds the file's directory */
    psz_char = strrchr( psz_path, DIR_SEP_CHAR );
    if( !psz_char )
    {
        free( psz_path );
        return 1;
    }
    *psz_char = '\0';

    /* Push package on stack */
    int count = 0;
    lua_getglobal( L, "package" );

    /* psz_path now holds the file's parent directory */
    count += vlclua_add_modules_path_inner( L, psz_path );
    *psz_char = DIR_SEP_CHAR;

    /* psz_path now holds the file's directory */
    count += vlclua_add_modules_path_inner( L, psz_path );

    char **ppsz_dir_list = NULL;
    vlclua_dir_list( psz_char+1/* gruik? */, &ppsz_dir_list );
    char **ppsz_dir = ppsz_dir_list;

    for( ; *ppsz_dir && strcmp( *ppsz_dir, psz_path ); ppsz_dir++ );
    free( psz_path );

    for( ; *ppsz_dir; ppsz_dir++ )
    {
        psz_path = *ppsz_dir;
        /* FIXME: doesn't work well with meta/... modules due to the double
         * directory depth */
        psz_char = strrchr( psz_path, DIR_SEP_CHAR );
        if( !psz_char )
        {
            vlclua_dir_list_free( ppsz_dir_list );
            return 1;
        }

        *psz_char = '\0';
        count += vlclua_add_modules_path_inner( L, psz_path );
        *psz_char = DIR_SEP_CHAR;
        count += vlclua_add_modules_path_inner( L, psz_path );
    }

    lua_getfield( L, -(count+1), "path" ); /* Get package.path */
    lua_concat( L, count+1 ); /* Concat vlc module paths and package.path */
    lua_setfield( L, -2, "path"); /* Set package.path */
    lua_pop( L, 1 ); /* Pop the package module */

    vlclua_dir_list_free( ppsz_dir_list );
    return 0;
}