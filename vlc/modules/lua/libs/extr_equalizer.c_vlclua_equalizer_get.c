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
typedef  scalar_t__ locale_t ;
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  LC_NUMERIC_MASK ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int asprintf (char**,char*,unsigned int) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  freelocale (scalar_t__) ; 
 int /*<<< orphan*/  lua_newtable (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushstring (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  lua_setfield (int /*<<< orphan*/ *,int,char*) ; 
 scalar_t__ newlocale (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 float strtof (char*,char**) ; 
 scalar_t__ uselocale (scalar_t__) ; 
 char* var_GetNonEmptyString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlclua_get_aout_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_equalizer_get( lua_State *L )
{
    const unsigned bands = 10;

    audio_output_t *p_aout = vlclua_get_aout_internal(L);
    if( p_aout == NULL )
        return 0;

    char *psz_af = var_GetNonEmptyString( p_aout, "audio-filter" );
    if( !psz_af || strstr ( psz_af, "equalizer" ) == NULL )
    {
        free( psz_af );
        aout_Release(p_aout);
        return 0;
    }
    free( psz_af );

    char *psz_bands_origin, *psz_bands;
    psz_bands_origin = psz_bands = var_GetNonEmptyString( p_aout, "equalizer-bands" );
    if( !psz_bands )
    {
        aout_Release(p_aout);
        return 0;
    }

    bool error = false;
    locale_t loc = newlocale (LC_NUMERIC_MASK, "C", NULL);
    locale_t oldloc = uselocale (loc);
    lua_newtable( L );
    for( unsigned i = 0; i < bands; i++ )
    {
        float level = strtof( psz_bands, &psz_bands );
        char *str;
        if( asprintf( &str , "%f" , level ) == -1 )
        {
            error = true;
            break;
        }
        lua_pushstring( L, str );
        free(str);
        if( asprintf( &str , "band id=\"%u\"", i ) == -1 )
        {
            error = true;
            break;
        }
        lua_setfield( L , -2 , str );
        free( str );
    }

    free( psz_bands_origin );
    if( loc != (locale_t)0 )
    {
        uselocale (oldloc);
        freelocale (loc);
    }
    aout_Release(p_aout);
    return error ? 0 : 1;
}