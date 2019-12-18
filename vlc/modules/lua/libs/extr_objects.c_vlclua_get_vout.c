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
 int /*<<< orphan*/  VLC_OBJECT (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  lua_pushnil (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * vlclua_get_vout_internal (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  vlclua_push_vlc_object (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vlclua_vout_release ; 

__attribute__((used)) static int vlclua_get_vout( lua_State *L )
{
    vout_thread_t *vout = vlclua_get_vout_internal(L);
    if (vout)
        vlclua_push_vlc_object(L, VLC_OBJECT(vout), vlclua_vout_release);
    else
        lua_pushnil(L);
    return 1;
}