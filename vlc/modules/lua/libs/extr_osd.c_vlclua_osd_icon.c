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
 char* luaL_checkstring (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*,char const*) ; 
 scalar_t__ luaL_optinteger (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int vlc_osd_icon_from_string (char const*) ; 
 int /*<<< orphan*/ * vlclua_get_vout_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_OSDIcon (int /*<<< orphan*/ *,int,int) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_osd_icon( lua_State *L )
{
    const char *psz_icon = luaL_checkstring( L, 1 );
    int i_icon = vlc_osd_icon_from_string( psz_icon );
    int i_chan = (int)luaL_optinteger( L, 2, VOUT_SPU_CHANNEL_OSD );
    if( !i_icon )
        return luaL_error( L, "\"%s\" is not a valid osd icon.", psz_icon );

    vout_thread_t *p_vout = vlclua_get_vout_internal(L);
    if( p_vout )
    {
        vout_OSDIcon( p_vout, i_chan, i_icon );
        vout_Release( p_vout );
    }
    return 0;
}