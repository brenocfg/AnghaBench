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
 int vlclua_playlist_add_common (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int vlclua_playlist_add(lua_State *L)
{
    return vlclua_playlist_add_common(L, true);
}