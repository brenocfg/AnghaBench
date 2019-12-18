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
typedef  int /*<<< orphan*/  vlc_tick_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  VLC_TICK_FROM_SEC (int) ; 
 int /*<<< orphan*/  VOUT_SPU_CHANNEL_OSD ; 
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 char* luaL_optstring (int /*<<< orphan*/ *,int,char*) ; 
 int /*<<< orphan*/  vlc_osd_position_from_string (char const*) ; 
 int /*<<< orphan*/ * vlclua_get_vout_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_OSDText (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_osd_message( lua_State *L )
{
    const char *psz_message = luaL_checkstring( L, 1 );
    int i_chan = (int)luaL_optinteger( L, 2, VOUT_SPU_CHANNEL_OSD );
    const char *psz_position = luaL_optstring( L, 3, "top-right" );
    vlc_tick_t duration = (vlc_tick_t)luaL_optinteger( L, 4, VLC_TICK_FROM_SEC(1));

    vout_thread_t *p_vout = vlclua_get_vout_internal(L);
    if( p_vout )
    {
        vout_OSDText( p_vout, i_chan, vlc_osd_position_from_string( psz_position ),
                      duration, psz_message );
        vout_Release( p_vout );
    }
    return 0;
}