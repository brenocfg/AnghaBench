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
 int NB_PRESETS ; 
 int asprintf (char**,char*,int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/ * preset_list_text ; 

__attribute__((used)) static int vlclua_equalizer_get_presets( lua_State *L )
{
    lua_newtable( L );
    char *str;
    for( int i = 0 ; i < NB_PRESETS ; i++ )
    {
        lua_pushstring( L, preset_list_text[i] );
        if( asprintf( &str , "preset id=\"%d\"",i ) == -1 )
            return 0;
        lua_setfield( L , -2 , str );
        free(str);
    }
    return 1;
}