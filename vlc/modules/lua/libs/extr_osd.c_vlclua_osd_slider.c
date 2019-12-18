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
typedef  int /*<<< orphan*/  vout_thread_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  VOUT_SPU_CHANNEL_OSD ; 
 int luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int vlc_osd_slider_type_from_string (char const*) ; 
 int /*<<< orphan*/ * vlclua_get_vout_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_OSDSlider (int /*<<< orphan*/ *,int,int,int) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_osd_slider( lua_State *L )
{
    int i_position = luaL_checkinteger( L, 1 );
    const char *psz_type = luaL_checkstring( L, 2 );
    int i_type = vlc_osd_slider_type_from_string( psz_type );
    int i_chan = (int)luaL_optinteger( L, 3, VOUT_SPU_CHANNEL_OSD );
    if( !i_type )
        return luaL_error( L, "\"%s\" is not a valid slider type.",
                           psz_type );

    vout_thread_t *p_vout = vlclua_get_vout_internal(L);
    if( p_vout )
    {
        vout_OSDSlider( p_vout, i_chan, i_position, i_type );
        vout_Release( p_vout );
    }
    return 0;
}