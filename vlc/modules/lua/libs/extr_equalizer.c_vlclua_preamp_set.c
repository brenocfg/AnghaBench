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
typedef  int /*<<< orphan*/  audio_output_t ;

/* Variables and functions */
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 char* var_GetNonEmptyString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetFloat (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlclua_get_aout_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_preamp_set( lua_State *L )
{
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

    var_SetFloat( p_aout, "equalizer-preamp", luaL_checknumber( L, 1 ) );
    aout_Release(p_aout);
    return 1;
}