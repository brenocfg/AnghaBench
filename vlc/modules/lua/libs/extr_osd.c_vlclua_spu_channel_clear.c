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
typedef  int /*<<< orphan*/  ssize_t ;
typedef  int /*<<< orphan*/  lua_State ;

/* Variables and functions */
 int /*<<< orphan*/  luaL_checkinteger (int /*<<< orphan*/ *,int) ; 
 int luaL_error (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * vlclua_get_vout_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_Release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vout_UnregisterSubpictureChannel (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_spu_channel_clear( lua_State *L )
{
    ssize_t i_chan = luaL_checkinteger( L, 1 );
    vout_thread_t *p_vout = vlclua_get_vout_internal(L);
    if( !p_vout )
        return luaL_error( L, "Unable to find vout." );

    vout_UnregisterSubpictureChannel( p_vout, i_chan );
    vout_Release(p_vout);
    return 0;
}