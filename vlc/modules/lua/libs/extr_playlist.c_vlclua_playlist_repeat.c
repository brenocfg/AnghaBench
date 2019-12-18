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
 int /*<<< orphan*/  VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT ; 
 int vlclua_playlist_repeat_ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int vlclua_playlist_repeat(lua_State *L)
{
    return vlclua_playlist_repeat_(L, VLC_PLAYLIST_PLAYBACK_REPEAT_CURRENT);
}