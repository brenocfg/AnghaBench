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
 int NB_PRESETS ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  free (char*) ; 
 int luaL_checknumber (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * preset_list ; 
 int /*<<< orphan*/ * strstr (char*,char*) ; 
 char* var_InheritString (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  var_SetString (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * vlclua_get_aout_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_equalizer_setpreset( lua_State *L )
{
    int presetid = luaL_checknumber( L, 1 );
    if( presetid >= NB_PRESETS || presetid < 0 )
        return 0;

    audio_output_t *p_aout = vlclua_get_aout_internal(L);
    if( p_aout == NULL )
        return 0;

    int ret = 0;
    char *psz_af = var_InheritString( p_aout, "audio-filter" );
    if( psz_af != NULL && strstr ( psz_af, "equalizer" ) != NULL )
    {
        var_SetString( p_aout , "equalizer-preset" , preset_list[presetid] );
        ret = 1;
    }
    free( psz_af );
    aout_Release(p_aout);
    return ret;
}