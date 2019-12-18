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
 int /*<<< orphan*/  aout_EnableFilter (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  aout_Release (int /*<<< orphan*/ *) ; 
 int luaL_checkboolean (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * vlclua_get_aout_internal (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int vlclua_equalizer_enable(lua_State *L)
{
    bool state = luaL_checkboolean(L , 1);
    audio_output_t *aout = vlclua_get_aout_internal(L);
    if (aout)
    {
        aout_EnableFilter(aout, "equalizer", state);
        aout_Release (aout);
    }
    return 0;
}